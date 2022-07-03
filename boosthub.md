# userDoc

## why boosthub?

1、why not use the FTP?

Of course, you can use the FTP tool, which is just a small personal project built for the fun of coding. It has great shortcomings, but I also want to use my own ideas to make my own satisfactory tools. So, we just think of it as an interesting little toy.  

2、network protocol

Custom communication protocols over TCP/IP. Custom communication protocols on top of TCP/IP, showcasing does not guarantee your data security, but will certainly do its best.  

3、Easy to deploy

Users without experience in program development and shell commands can also quickly deploy and run on the server and operate on their file repositories with remote clients.

4、Just to be clear

It's more like a useful, useless little toy that can also be used when needed.

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
