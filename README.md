Self-hosting a Rathole Gateway
Prerequisites:
1. A public server with a static IP or domain to act as the gateway.
2. A client machine (your internal service that will be tunneled).
3. Rathole installed on both the gateway and the client.
Installation:
1. Install Rathole
On both the gateway and client, download and install Rathole:
# Download Rathole on both machines
curl -LO https://github.com/rapiz1/rathole/releases/download/v0.4.6/rathole-linux-amd64.tar.gz
# Extract the downloaded file
tar -zxvf rathole-linux-amd64.tar.gz
# Move the binary to /usr/local/bin
sudo mv rathole /usr/local/bin/
# Check if Rathole is properly installed
rathole -V
# 2. Configure the Gateway (Public Server)
Create a gateway-config.toml file for the gateway, which will handle connections from the client:
- sudo nano /etc/rathole/gateway-config.toml
- Inside the gateway-config.toml, configure the gateway like this:
- [server]
- bind_addr = "0.0.0.0:2333" # Listen address for public traffic
- max_tunnels = 100 # Max number of tunnels the server can handle
# [server.tunnels.example-tunnel]
- bind_addr = "127.0.0.1:8080" # The service you want to expose on the gateway
- token = "your_secret_token" # Shared token for authentication with the client
# 3. Configure the Client
On your client machine, create a client-config.toml file.
- sudo nano /etc/rathole/client-config.toml
- Here's an example configuration for the client:
- [client]
- remote_addr = "your-public-server-ip:2333" # Address of your public gateway server
- retry_interval = 5 # Retry interval if connection fails
[client.tunnels.example-tunnel]
- local_addr = "127.0.0.1:8080" # Address of the local service
- token = "your_secret_token" # Shared secret, must match the gateway config
# 4. Start Rathole
On the Gateway:
- rathole -c /etc/rathole/gateway-config.toml
# On the Client:
- rathole -c /etc/rathole/client-config.toml
Test the Setup:
Now, traffic to your-public-server-ip:2333 will be forwarded to the internal service on the client
machine running on 127.0.0.1:8080.
