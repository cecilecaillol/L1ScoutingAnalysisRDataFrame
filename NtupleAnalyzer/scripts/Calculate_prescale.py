import subprocess
import json

# Define the dataset name
#dataset = "/L1Scouting/Run2024H-v1/L1SCOUT"
#dataset = "/L1Scouting/Run2024G-v1/L1SCOUT"
dataset = "/L1Scouting/Run2024I-v1/L1SCOUT"

# Step 1: Get the list of runs
cmd_runs = f"dasgoclient -json -query='run dataset={dataset}'"
runs_output = subprocess.check_output(cmd_runs, shell=True)
runs_data = json.loads(runs_output)

# Extract run numbers
runs = [entry['run'][0]['run_number'] for entry in runs_data]

# Step 2: Loop over runs and sum lumis
total_lumis = 0

#for run in runs:
#    cmd_lumis = f"dasgoclient -json -query='lumi run={run} dataset={dataset}'"
#    lumis_output = subprocess.check_output(cmd_lumis, shell=True)
#    lumis_data = json.loads(lumis_output)
#
#    # Count the number of lumis for this run
#    for entry in lumis_data:
#        total_lumis += len(entry['lumi'])

# Step 3: Get total number of events
cmd_events = f"dasgoclient -json -query='summary dataset={dataset}'"
events_output = subprocess.check_output(cmd_events, shell=True)
events_data = json.loads(events_output)
print(events_data)

## Extract total number of events
#total_events = events_data[0]['summary']['nevents'] if events_data else 0

## Step 4: Compute the ratio (avoid division by zero)
#lumi_event_ratio = total_lumis / total_events if total_events > 0 else float('inf')

print(f"Total number of lumis: {total_lumis}")
#print(f"Total number of events: {total_events}")
#print(f"Lumis per event: {lumi_event_ratio:.6f}")
#print("Prescale: ", total_lumis* (2**18) / total_events)
