#!/bin/bash

# List of server URLs (Epic Games and Nepali Minecraft servers)
servers=(
    "ping-nae.ds.on.epicgames.com"
    "ping-nac.ds.on.epicgames.com"
    "ping-naw.ds.on.epicgames.com"
    "ping-eu.ds.on.epicgames.com"
    "ping-oce.ds.on.epicgames.com"
    "ping-br.ds.on.epicgames.com"
    "ping-asia.ds.on.epicgames.com"
    "ping-me.ds.on.epicgames.com"
    "play.craftnepal.net"
    "play.infinityrealms.xyz"
    "play.voidmc.us.to"
)

# Ping each server once and extract the latency
for server in "${servers[@]}"
do
    echo -n "$server: "
    ping -c 1 $server | grep 'time=' | awk -F 'time=' '{ print $2 }' | cut -d ' ' -f 1
done
