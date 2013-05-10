#!/bin/bash

#Programmer: Valerie Gray
#Purpose: This script creates that xml and macro files
#for the MD9 bar study in Geant4
#
#This will create root files for simulations in 
#octants 1, 8, 7 for MD9 positions at nominal and
# +- 5 mm from nominal
#
#Date: 11-22-2012
#Modified:
#Assisted By: Wouter Deconinck
#

# comment

basename=myPosDirScan

#min and max beam poitions (um)
position_min=-2000
position_max=2000
position_step=500

#min and max direction(angle) in (urad)
direction_min=-600
direction_max=600
direction_step=300

#first job number (can change if just want to add
#on to the get more simultaions)
firstjob=1
#total number of jobs one would like done
njobs=50
#number of events simulated in each Geant4 file
nevents=125000

#go through each axis changing postion and direction
for axis in X Y ; do
	echo "axis = ${axis}"

  #start with only changing the position
	let direction=0
	let position=${position_min}
	while [[ ${position} -le ${position_max} ]] ; do
		echo "position = ${position}"
		echo "direction = ${direction}"

    #come up with the basename that will be used  to name the rootfiles
		name=${basename}_Pos${axis}_${position}um_Dir${axis}_${direction}urad

		let jobid=${firstjob}
  	while [[ ${jobid} -le ${njobs} ]] ; do
			echo "Job ${jobid}"

      #create a randome seed so that the simultaions are not all the same
			unixtime=`date +%s`
			nanosecond=`date +%N`
			let seedA=10#${unixtime}+${position}+${jobid}
			let seedB=10#${nanosecond}+${position}+${jobid}

			mkdir -p random/${name}_${jobid}
			mkdir -p jobs/xml
			mkdir -p macros/jobs

      #replace the variables in the file macros/${basename}.in
      #which creates the mac file that Geant4 uses
			sed -e "s/%position%/${position}/g" \
					-e "s/%direction%/${direction}/g" \
					-e "s/%axis%/${axis}/g" \
					-e "s/%nevents%/${nevents}/g" \
					-e "s/%seedA%/${seedA}/g" \
					-e "s/%seedB%/${seedB}/g" \
					-e "s/%jobid%/${jobid}/g" \
					-e "s/%basename%/${basename}/g" \
					-e "s/%name%/${name}/g" \
				macros/${basename}.in \
			> macros/jobs/${name}_${jobid}.mac

      #replace the variables in the file ${basename}.in
      #which creates the xml file that is submitted to the farm
			sed -e "s/%position%/${position}/g" \
					-e "s/%direction%/${direction}/g" \
					-e "s/%axis%/${axis}/g" \
					-e "s/%nevents%/${nevents}/g" \
					-e "s/%seedA%/${seedA}/g" \
					-e "s/%seedB%/${seedB}/g" \
					-e "s/%jobid%/${jobid}/g" \
					-e "s/%basename%/${basename}/g" \
					-e "s/%name%/${name}/g" \
				jobs/${basename}.in \
			> jobs/xml/${name}_${jobid}.xml

      #define where the rootfile will be stored, check to see if a rootfile  
      #exists, if not then submit the job if it is there do not submit it 
      #if so then move to the next job
			rootfile=/mss/home/vmgray/rootfiles/${basename}/${name}_${jobid}.root
			if [ ! -e ${rootfile} ] ; then
				echo "File ${rootfile} doesn't exist. Will submit job."
				jsub -xml jobs/xml/${name}_${jobid}.xml
			else
				echo "File ${rootfile} already exists."
			fi

			let jobid=${jobid}+1
		done

		let position=${position}+${position_step}
	done

  #finish with only changing the direction
	let position=0
	let direction=${direction_min}
	while [[ ${direction} -le ${direction_max} ]] ; do
		echo "position = ${position}"
		echo "direction = ${direction}"

    #come up with the basename that will be used  to name the rootfiles
		name=${basename}_Position${axis}_${position}um_Direction${axis}_${direction}urad

		let jobid=${firstjob}
  	while [[ ${jobid} -le ${njobs} ]] ; do
			echo "Job ${jobid}"

      #create a randome seed so that the simultaions are not all the same
			unixtime=`date +%s`
			nanosecond=`date +%N`
			let seedA=10#${unixtime}+${direction}+${jobid}
			let seedB=10#${nanosecond}+${direction}+${jobid}

			mkdir -p random/${name}_${jobid}
			mkdir -p jobs/xml
			mkdir -p macros/jobs

      #replace the variables in the file macros/${basename}.in
      #which creates the mac file that Geant4 uses
			sed -e "s/%position%/${position}/g" \
					-e "s/%direction%/${direction}/g" \
					-e "s/%axis%/${axis}/g" \
					-e "s/%nevents%/${nevents}/g" \
					-e "s/%seedA%/${seedA}/g" \
					-e "s/%seedB%/${seedB}/g" \
					-e "s/%jobid%/${jobid}/g" \
					-e "s/%basename%/${basename}/g" \
					-e "s/%name%/${name}/g" \
				macros/${basename}.in \
			> macros/jobs/${name}_${jobid}.mac

      #replace the variables in the file ${basename}.in
      #which creates the xml file that is submitted to the farm
			sed -e "s/%position%/${position}/g" \
					-e "s/%direction%/${direction}/g" \
					-e "s/%axis%/${axis}/g" \
					-e "s/%nevents%/${nevents}/g" \
					-e "s/%seedA%/${seedA}/g" \
					-e "s/%seedB%/${seedB}/g" \
					-e "s/%jobid%/${jobid}/g" \
					-e "s/%basename%/${basename}/g" \
					-e "s/%name%/${name}/g" \
				jobs/${basename}.in \
			> jobs/xml/${name}_${jobid}.xml

      #define where the rootfile will be stored, check to see if a rootfile  
      #exists, if not then submit the job if it is there do not submit it 
      #if so then move to the next job
			rootfile=/mss/home/vmgray/rootfiles/${basename}/${name}_${jobid}.root
			if [ ! -e ${rootfile} ] ; then
				echo "File ${rootfile} doesn't exist. Will submit job."
				jsub -xml jobs/xml/${name}_${jobid}.xml
			else
				echo "File ${rootfile} already exists."
			fi

			let jobid=${jobid}+1
		done

		let direction=${direction}+${direction_step}
	done


done
