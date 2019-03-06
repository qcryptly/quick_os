container_name=qos
image_base=qcryptly/quick_os:latest
cmd=/bin/bash
if [ $(docker ps -a | grep $container_name | wc -l) -gt 0 ]; then
	docker start -a $container_name
else
	docker run -it --name $container_name --user $(id -u):$(id -g) -v $(pwd):/src $image_base $cmd 
fi
