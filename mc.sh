#!/bin/bash

# Base URL
base_url="https://minecraftservers.org/index"

# File to store all IP addresses
all_ips_file="all_ips.txt"
results_file="ping_results.txt"
sorted_results_file="sorted_ping_results.txt"

# Initialize or clear the IPs file and results file
> "$all_ips_file"
echo "Server IP,Latency (ms)" > "$results_file"

echo "Starting to process pages..."

# Loop through pages 1 to 10
for page_number in $(seq 1 984); do
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

echo "Pinging IP addresses..."

# Count the number of IPs to estimate progress
total_ips=$(wc -l < "$all_ips_file")

# Loop through each IP address and ping it
while IFS= read -r ip; do
    if [[ -n "$ip" ]]; then
        # Ping the server and extract the latency
        latency=$(ping -c 1 "$ip" 2>/dev/null | grep 'time=' | sed 's/.*time=\(.*\) ms/\1/')
        
        if [[ -z "$latency" ]]; then
            latency="Unreachable"
        fi
        
        # Append the result to the file
        echo "$ip,$latency" >> "$results_file"
    fi
done < "$all_ips_file" | pv -l -s "$total_ips" > /dev/null

echo "Sorting results..."
# Sort the results by latency
awk -F, '{ if ($2 ~ /^[0-9]+$/) print $1","$2; else print $1",1000000" }' "$results_file" | sort -t, -k2,2n > "$sorted_results_file"

echo "Displaying sorted results..."
# Display the sorted results
cat "$sorted_results_file"

# Clean up
rm "$all_ips_file" "$results_file"
