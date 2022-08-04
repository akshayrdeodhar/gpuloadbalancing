# Simple Process Dumper
- All nodes share a common NFS for storing dumped processes. Path of the NFS is known to all.
- Agent runs on all nodes
	- Serves one socket (for calls from our "runtime"), to be made by programs which want to be frozen
	- Serves another socket (for calls from the "master" or from an authorized client, instructing it to _restore_ 
	  a process from some URI)

- Simplification: Whatever can be easily dumped, will be dumped, not complications for now. We are not responsible for moving any files over- if you can manage to have a shared filesystem do it- this tool offers no guarentees.
- Note: the "sockets" could be replaced by an RPC API- cleaner, and easier to interact with.

- We have a master that either monitors some common state store (better) or the agents call the master when they are freezing a program to let it know that 

## NFS Setup
- Install nfs
```
	pacman -S nfs
```

- Modify /etc/nfs.conf to specify the hostnames on which to serve the nfs server
- Modify /etc/exports to specify the directory subtree to export, and the users to whom access is to be provided. eg.
```
	$cat /etc/exports
	/home/akshay/Desktop/dumpdir	*(rw,sync)
	# provide synchronous read-write access to the subtree /home/akshay/Desktop/dumpdir
```
- Start the nfs server, and export directories:
```
	systemctl start nfs-server.service
	exportfs -r
```

- Mount NFS at same path on all nodes in our "load balancing cluster"
```
	mount -t nfs <central server ip address on lan>:/home/akshay/Desktop/dumpdir /mnt/dump
```

- Bind mount to same path on the node which is serving the nfs export
```
	mount --bind /home/akshay/Desktop/dumpdir /mnt/dump

- Now, everyone sees the same files at /mnt/dump

- Now, shared files accessible at /mnt/dump- because its just one server, you get unix semantics. 
