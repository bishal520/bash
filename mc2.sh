#!/bin/bash

# Base URL
base_url="https://minecraftservers.org/index"

# File to store all IP addresses
all_ips_file="all_ips.txt"
results_file="ping_results.txt"
sorted_results_file="sorted_ping_results.txt"
max_jobs=10000000000000000

# Initialize or clear the IPs file and results file
> "$all_ips_file"
echo "Server IP,Latency (ms)" > "$results_file"

echo "Starting to process pages..."

# Loop through pages 1 to 10
for page_number in $(seq 1 900); do
    echo "Processing page $page_number..."
    # Download the webpage for the current page
    wget -q -O "page_${page_number}.html" "${base_url}/${page_number}"

    # Extract server IP addresses
    grep -oP '(?<=<div>)[^<]+(?=</div>)' "page_${page_number}.html" >> "$all_ips_file"

    # Clean up the downloaded HTML file
    rm "page_${page_number}.html"
done

echo "Removing duplicate IPs..."
# Remove duplicate IP addresses
sort -u "$all_ips_file" -o "$all_ips_file"

# File to store unsorted ping results
> "$results_file"

echo "Pinging IP addresses in parallel..."

# Function to ping a server and save the result
ping_server() {
    ip=$1
    latency=$(ping -c 1 -W 1 "$ip" 2>/dev/null | grep 'time=' | sed 's/.*time=\(.*\) ms/\1/')
    if [[ -z "$latency" ]]; then
        latency="Unreachable"
    fi
    echo "$ip,$latency"
}

export -f ping_server

# Use background processes with a job control mechanism
job_count=30
while IFS= read -r ip; do
    if [[ -n "$ip" ]]; then
        ping_server "$ip" >> "$results_file" &
        job_count=$((job_count + 1))
        if (( job_count >= max_jobs )); then
            wait -n  # Wait for at least one background job to finish
            job_count=$((job_count - 1))
        fi
    fi
done < "$all_ips_file"

# Wait for remaining background jobs to complete
wait

echo "Sorting results..."
# Sort the results by latency
awk -F, '{ if ($2 ~ /^[0-9]+$/) print $1","$2; else print $1",1000000" }' "$results_file" | sort -t, -k2,2n > "$sorted_results_file"

echo "Displaying sorted results..."
# Display the sorted results
cat "$sorted_results_file"

# Clean up
rm "$all_ips_file" "$results_file"
