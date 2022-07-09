# Document

quick start about boosthub,lightweight file transition

## quick run

```bash
sudo bash ./boosthub.sh
```

## start server or shell client

```bash
sudo boosthub --server 0.0.0.0 8080  
# start the server-side boothub service  

sudo boosthub --shell 127.0.0.1 8080  
# client shell connection server  
```

## web client

using chrome to visit the web page  

* index page  

`IP:8080/`or`IP:8080/index.html`  

![indexpage](./img/indexpage.jpg)

* upload page

`IP:8080/upload` or `IP:8080/upload.html`  

![uploadpage](./img/uploadpage.jpg)

## client shell

### `ls`  

view the file and directory information under the location

```shell
>> ls
```

```shell
Now Path: /     This Path Inner Sum: 26 
Fd: 83406 Name: . Type:d 
Fd: 83406 Name: .. Type:d 
Fd: 83460 Name: hub Type:d 
Fd: 83461 Name: safe Type:d 
Fd: 83462 Name: boosthub Type:d 
```  

### `cd [Folder path]`

switch the current path

```shell
>> cd /var

Now Path: /var  

>> cd ./www

Now Path: /var/www  

>> ls

Now Path: /var/www     This Path Inner Sum: 3 
Fd              	Name            	Type            
762671          	.               	d               
762671          	..              	d               
762672          	html            	d               

>>cd ./html

Now Path: /var/www/html  

>> ls

Now Path: /var/www/html     This Path Inner Sum: 2 

Fd              	Name            	Type            
762672          	.               	d               
762672          	..              	d               
>>
```

### `pwd`

view the path at this time

```shell
>> cd /var/www
Now Path: /var/www  
>> cd ../
Now Path: /var  
>> pwd
Now Path: /var 
```

### `get [File path]`

gets the byte stream of the specified file

```shell
>> ls
Now Path: /mnt/c/slago/build/static/js     This Path Inner Sum: 3 

Fd              	Name            	Type            
1339378         	.               	d               
1339378         	..              	d               
1339413         	hello.js	        f               

>> get ./hello.js  

console.log("Hello Boosthub"); 
```

## http upload

a example for curl  

```bash
curl --location --request POST 'http://127.0.0.1:8080/' \
--header 'Content-Type: video/mp4' \
--data-binary '@/C:/Users/gaowanlu/Videos/IMG_0895.mp4'
```

how find file that was uploaded with http  

```cpp
boosthub/bin/warehouse
```

the format of file  

```bash
2022-5-3-0:59:8_7.body
```
