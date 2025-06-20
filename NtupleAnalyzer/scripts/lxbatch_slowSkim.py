import os

# Define input and output directories
input_dir = "/eos/cms/store/group/cmst3/group/slowmuons/Mu8Skim/L1Scouting"
output_dir = "/eos/cms/store/group/cmst3/group/slowmuons/SlowSkims"
exe_script = "/afs/cern.ch/work/c/ccaillol/L1ScoutingAnalysisRDataFrame/CMSSW_14_0_12/src/L1ScoutingAnalysisRDataFrame/NtupleAnalyzer/scripts/FinalSelection_SlowData.py"

# Ensure output and logs directory exist
os.makedirs(output_dir, exist_ok=True)
os.makedirs("logs_slow", exist_ok=True)
os.makedirs("wrappers_slow", exist_ok=True)

# HTCondor submit file template
submit_template = """\
universe   = vanilla
executable = {wrapper}
arguments  = {input} {output}
output     = logs_slow/{job_name}.out
error      = logs_slow/{job_name}.err
log        = logs_slow/{job_name}.log
+JobFlavour = "workday"
+AccountingGroup = "group_u_CMST3.all"
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
queue
"""

# Iterate over input files and create submission and wrapper files
for input_file in os.listdir(input_dir):
    if input_file.endswith(".root"):
        input_path = os.path.join(input_dir, input_file)
        output_path = os.path.join(output_dir, f"output_{input_file}")
        job_name = os.path.splitext(input_file)[0]  # Remove extension

        # Create a wrapper script for each job
        wrapper_script = f"wrappers_slow/wrapper_{job_name}.sh"
        with open(wrapper_script, "w") as wf:
            wf.write(f"""#!/bin/bash
# Wrapper script to setup CMS environment and run analysis

echo "Setting up CMS environment..."
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/cern.ch/work/c/ccaillol/L1ScoutingAnalysisRDataFrame/CMSSW_14_0_12/src
eval `scramv1 runtime -sh`

echo "Running python script..."
python3 {exe_script} {input_path} {output_path}
""")
        os.chmod(wrapper_script, 0o755)  # Make the wrapper executable

        # Create the submit file
        submit_file = f"submit_slow_{job_name}.sub"
        with open(submit_file, "w") as f:
            f.write(submit_template.format(
                wrapper=wrapper_script,
                input=input_path,
                output=output_path,
                job_name=job_name
            ))

        # Submit the job
        os.system(f"condor_submit {submit_file}")

print("All jobs submitted!")

