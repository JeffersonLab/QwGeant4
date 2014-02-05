#!/usr/bin/env perl
use strict;
use warnings;

use Getopt::Long;
use Data::Dumper;

###############################################################################
##Quick program to submit a series of simulations to 
##Auger. Please see the help menu by running --help.
##
##Author: Josh Magee, magee@jlab.org
##June 7, 2013.
###############################################################################

#declaration of global variables, arrays, and hashes
my $user = getpwuid($<);  #get user id
my $original_mac;
my $jobname;
my $mac_content;
my $Nevents;
my $Njobs;

#declaration of subroutines
sub helpscreen;
sub print_header;   #prints macfile header
sub print_footer;   #prints macfile footer
sub print_xml;      #prints xml file

my ($help,$dryrun,$outfile);
GetOptions(
 "help|h|?"           =>  \$help,
 "Nevents|events=i"   =>  \$Nevents,
 "Njobs|jobs=i"       =>  \$Njobs,
 "dry-run|dry|test"   =>  \$dryrun,
 "outfile|out|o=s"    =>  \$outfile,
);

#die helpscreen unless $#ARGV!=0;
die helpscreen if $help;
#create necessary directories unless exists
mkdir "xml" unless (-e "xml");
mkdir "macros" unless (-e "macros");
mkdir "jsub" unless (-e "jsub");
mkdir "jsub/output" unless (-e "jsub/output");

$Njobs  = 10   unless  $Njobs;
$Nevents=10000 unless $Nevents;
$original_mac = pop @ARGV;

#construct basename
#basename is the name of the original macfile given
#with a number appended, 1<n<Njobs
if ($original_mac =~ m/(.*)\.mac/) {
    $jobname = $1;
} else {
    $jobname = $original_mac;
    $original_mac = $original_mac . "\.mac";
}

#open and read-in provided mac file
open ORIG, "<", $original_mac or die "cant open your .mac file: $!\n";
{
  local $/;               #restrict slurp to local block
  $mac_content = <ORIG>;  #SLUUUUUURP
}
close ORIG;

foreach my $number (1..$Njobs) {
  my $basename = "$jobname\_$number";
  my $output = "macros\/$basename\.mac";
  my $xmlout = "xml\/$basename.xml";

  #create individual macfile
  open my $fh, ">", $output or die "can't open/create $output: $!\n";
  print_header($fh,$basename);  #print new title
  print $fh $mac_content;
  print_footer($fh,$basename,$Nevents); #print random seed information, output
  close $fh;

  #create xml file
  open my $xml, ">", $xmlout or die "can't open/create $xmlout: $!\n";
  print_xml($xml,$basename);
  close $xml;

  if ($dryrun) {
    print "This is just a test: jsub -xml $xmlout\n";
  } else {
    my $callAuger = "jsub -xml $xmlout";  #this is command to run jobs
    system $callAuger;
  }
} #end foreach over files

print "End of job submissions.\n";

exit;


###############################################################################
### End of main logic. Subroutines defined below.
###############################################################################


sub helpscreen {
my $helpstring = <<EOF;
Program designed to submit multiple jobs to the Auger batchfarm.
Provide this script with a map file, the number of events to
generate, and the number of files to generate, and it will do
the rest.

Calling syntax:
  g4jsub.pl [options]
Example:
  g4sub.pl sample.mac --events 20000 --jobs 5 -o "/work/username/directory"

Options include:
  --help       displays this helpful message
  --events     set number of events in each job
                default is 10k
  --jobs       number of jobs to submit
                default is 10
  --outfile    provide an output file location
                default is /volatile/hallc/qweak/USERNAME
  --dry-run    do a dry run: create all the files
                but don't submit any.
                Useful for testing.
EOF
die $helpstring if $help;
}

sub print_header {
  my ($fh,$basename) = @_;

  my $header =
"
#==============================#
# Macro file $basename         #
# generated from g4jsub script #
#==============================#
";
print $fh "$header\n";
}

sub print_footer {
  my ($fh,$basename,$Nevents) = @_;

  my $seed1 = int ( rand(1e10) );
  my $seed2 = int ( rand(1e9 ) );

  if ( $outfile ) {
    #if the given outfile destination ends with a "/", chop it. I'll add it back in.
    chop $outfile if $outfile =~ m/\/$/;
    $outfile = "$outfile/$basename.root";
  } else {
    $outfile = "/volatile/hallc/qweak/$user/$basename.root";
  }

  my $footer =
  "
# load/execute this macro
/random/setSeeds $seed1 $seed2
/Analysis/RootFileName $outfile
/run/beamOn $Nevents
";

print $fh "$footer\n";
return;
}

sub print_xml {
  my ($xml,$basename) = @_;

my $xmlfile =
"
<Request>
  <Email email=\"$user\@jlab.org\" request=\"false\" job=\"true\"/>
  <Project name=\"qweak\"/>
  <Track name=\"simulation\"/>
  <Name name=\"$basename\"/>
  <OS name=\"centos62\"/>
  <Command><![CDATA[
source /home/$user/.login
cd /u/home/$user/QwGeant4/
build/QweakSimG4 macros/$basename\.mac
  ]]></Command>

  <Memory space=\"1200\" unit=\"MB\"/>

  <Job>
    <Stdout dest=\"/u/home/$user/QwGeant4/jsub/output/$basename\.out\"/>
    <Stderr dest=\"/u/home/$user/QwGeant4/jsub/output/$basename\.err\"/>
  </Job>

</Request>
";
print $xml "$xmlfile\n";
return;
} #end print_xml

