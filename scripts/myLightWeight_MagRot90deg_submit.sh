#!/bin/bash

#Programmer: Valerie Gray
#Purpose: This script creates that xml and macro files
#for the Light weighting study in Geant4 on LH2 with a 90
#degree rotaiton in the magnetic field
#
#Date: 11-22-2012
#Modified:1-25-2013
#Assisted By: Wouter Deconinck
#

name=myLightWeightScan_MagRot90deg

#first job number (can change if just want to add
#on to the get more simultaions)
firstjob=1301
#last number of jobs one would like done
lastjob=2500
#number of events simulated in each Geant4 file
nevents=125000

let jobid=${firstjob}
 while [[ ${jobid} -le ${lastjob} ]] ; do
	echo "Job ${jobid}"

  #create a randome seed so that the simultaions are not all the same
	unixtime=`date +%s`
	nanosecond=`date +%N`
	let seedA=10#${unixtime}+${current}+${jobid}
	let seedB=10#${nanosecond}+${current}+${jobid}

	mkdir -p random/${name}_${jobid}
	mkdir -p jobs/xml
	mkdir -p macros/jobs

  #replace the variables in the file macros/${basename}.in
  #which creates the mac file that Geant4 uses
	sed -e "s/%nevents%/${nevents}/g" \
			-e "s/%seedA%/${seedA}/g" \
			-e "s/%seedB%/${seedB}/g" \
			-e "s/%jobid%/${jobid}/g" \
			-e "s/%name%/${name}/g" \
		macros/${name}.in \
	> macros/jobs/${name}_${jobid}.mac

  #replace the variables in the file ${basename}.in
  #which creates the xml file that is submitted to the farm
	sed -e "s/%nevents%/${nevents}/g" \
			-e "s/%seedA%/${seedA}/g" \
			-e "s/%seedB%/${seedB}/g" \
			-e "s/%jobid%/${jobid}/g" \
			-e "s/%name%/${name}/g" \
		jobs/${name}.in \
	> jobs/xml/${name}_${jobid}.xml

  #define where the rootfile will be stored, check to see if a rootfile  
  #exists, if not then submit the job if it is there do not submit it 
  #if so then move to the next job
  rootfile=/mss/home/vmgray/rootfiles/${name}/${name}_${jobid}.root
  if [ ! -e ${rootfile} ] ; then
    echo "File ${rootfile} doesn't exist. Will submit job."
    jsub -xml jobs/xml/${name}_${jobid}.xml
  else
    echo "File ${rootfile} already exists."
  fi

	let jobid=${jobid}+1
done
