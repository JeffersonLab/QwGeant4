#!/bin/bash

#Programmer: Valerie Gray
#Purpose: This script creates the job and macro files
#for the Light weighting study in Geant4 on LH2
#
#Date: 11-22-2012
#Modified: 1-25-2013
#Assisted By: Wouter Deconinck
#

name=myTrackingRun
tag=_LH2_4x4mm_oct15_dir15x0mrad

#first job number (can change if just want to add
#on to the get more simulations)
firstjob=1
#total number of jobs one would like done
lastjob=199
#number of events simulated in each Geant4 file
nevents=200000
#batch system
batch=xml

#find geant4 base installation directory
qwgeant4=`dirname $0`
qwgeant4=`readlink -f $qwgeant4/..`
mkdir -p /home/${USER}/scratch

let jobid=${firstjob}
 while [[ ${jobid} -le ${lastjob} ]] ; do
	echo "Job ${jobid}"

	#create a randome seed so that the simultaions are not all the same
	unixtime=`date +%s`
	nanosecond=`date +%N`
	let seedA=10#${unixtime}+${current}+${jobid}
	let seedB=10#${nanosecond}+${current}+${jobid}

	mkdir -p random/${name}${tag}_${jobid}
	mkdir -p jobs/${batch}
	mkdir -p macros/jobs

	#replace the variables in the file macros/${basename}.in
	#which creates the mac file that Geant4 uses
	sed -e "s|%nevents%|${nevents}|g" \
			-e "s|%qwgeant4%|${qwgeant4}|g" \
			-e "s|%seedA%|${seedA}|g" \
			-e "s|%seedB%|${seedB}|g" \
			-e "s|%jobid%|${jobid}|g" \
			-e "s|%name%|${name}${tag}|g" \
		macros/${name}.in \
	> macros/jobs/${name}${tag}_${jobid}.mac

	#replace the variables in the file ${basename}.in
	#which creates the job file that is submitted to the farm
	sed -e "s|%nevents%|${nevents}|g" \
			-e "s|%qwanalysis%|${QWANALYSIS}|g" \
			-e "s|%qwscratch%|${QWSCRATCH}|g" \
			-e "s|%qwgeant4%|${qwgeant4}|g" \
			-e "s|%seedA%|${seedA}|g" \
			-e "s|%seedB%|${seedB}|g" \
			-e "s|%jobid%|${jobid}|g" \
			-e "s|%name%|${name}${tag}|g" \
			-e "s|%user%|${USER}|g" \
		jobs/tracking.${batch}.in \
	> jobs/${batch}/${name}${tag}_${jobid}.${batch}

	#define where the rootfile will be stored, check to see if a rootfile  
	#exists, if not then submit the job if it is there do not submit it 
	#if so then move to the next job
	rootfile=/mss/home/${USER}/rootfiles/${name}/${name}${tag}_${jobid}_tracking.root
	if [ -e ${rootfile} ] ; then
		echo "File ${rootfile} already exists on mss."
	else
		echo "File ${rootfile} doesn't exist. Will submit job."
		if [ "${batch}" == "xml" ] ; then
			jsub -xml jobs/${batch}/${name}${tag}_${jobid}.${batch}
		fi
		if [ "${batch}" == "sh" ] ; then
			echo "Submitting job jobs/${batch}/${name}${tag}_${jobid}.${batch}..."
			qsub jobs/${batch}/${name}${tag}_${jobid}.${batch}
		fi
	fi

	#increase the jobid number
	let jobid=${jobid}+1
done

# :)
