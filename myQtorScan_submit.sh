#Programmer: Valerie Gray
#Purpose: This script creates that xml and macro files
#for the Qtor scan study in Geant4
#
#Date: 11-22-2012
#Modified:
#Assisted By: Wouter Deconinck
#
#!/bin/bash

# comment

basename=myQtorScan

#min and max current values
current_min=8000
current_max=9000
current_step=20

#first job number (can change if just want to add
#on to the get more simultaions)
firstjob=1
#number of jobs
njobs=50
#number of events per job
nevents=125000

let current=${current_min}
while [[ ${current} -le ${current_max} ]] ; do
	echo "current = ${current}"

  #come up with the basename that will be used  to name the rootfiles
	name=${basename}_${current}

	let jobid=${firstjob}
 	while [[ ${jobid} -le ${njobs} ]] ; do
		echo "Job ${jobid}"

    #create a randome seed so that the simultaions are not all the same
		unixtime=`date +%s`
		nanosecond=`date +%N`
		let seedA=10#${unixtime}+${position}+${jobid}
		let seedB=10#${nanosecond}+${position}+${jobid}

		mkdir -p random/${name}_${jobid}

    #replace the variables in the file macros/${basename}.in
    #which creates the mac file that Geant4 uses
		sed -e "s/%current%/${current}/g" \
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
		sed -e "s/%current%/${current}/g" \
				-e "s/%nevents%/${nevents}/g" \
				-e "s/%seedA%/${seedA}/g" \
				-e "s/%seedB%/${seedB}/g" \
				-e "s/%jobid%/${jobid}/g" \
				-e "s/%basename%/${basename}/g" \
				-e "s/%name%/${name}/g" \
			${basename}.in \
		> jobs/${name}_${jobid}.xml

    #define where the rootfile will be stored, check to see if a rootfile  
    #exists, if not then submit the job if it is there do not submit it 
    #if so then move to the next job
		rootfile=/mss/home/vmgray/rootfiles/${basename}/${name}_${jobid}.root
		if [ ! -e ${rootfile} ] ; then
			echo "File ${rootfile} doesn't exist. Will submit job."
			jsub -xml jobs/${name}_${jobid}.xml
		else
			echo "File ${rootfile} already exists."
		fi

		let jobid=${jobid}+1
	done

	let current=${current}+${current_step}
done
