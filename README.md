<!-- PROJECT LOGO -->
<br />
<div align="center">
  <h2 align="center">Boosthub</h2>

  <p align="center">
    Linux applications for lightweight file storage repositories and file transfer tools .
    <br />
    <a href="https://github.com/gaowanlu/boosthub"><strong>DOC »</strong></a>
    <br />
    <br />
  </p>
</div> 





## Introduction  
Using Boosthub you can store your file repository on the server side, and you can operate the repository on the client side.    

Boosthub is an extremely simple application that doesn't require other Linux applications to rely on .  

## Framework Base  

<div align="center">

![framework base](./images/3835BCB193E583DBC3CEE458262128A2.png)  

</div>

 


## Quick Start 
###  Ⅰ.Prepare  
```  
$ sudo apt update 
$ sudo apt install g++ gcc make cmake git 
$ sudo apt install glibc-doc manpages-posix-dev 
``` 

### Ⅱ.Get Boosthub
```shell 
$ git clone https://github.com/gaowanlu/boosthub.git  
$ cd ./boosthub 
$ cmake . 
$ make 
$ make install 
```
```code 
...
[100%] Built target boosthub
Install the project...
-- Install configuration: ""
-- Installing: /usr/bin/boosthub
```
### Ⅲ.Use Boosthub  
```
$ boosthub --help  
Disclaimer: no client can use it at present. 
It can only be connected through socket. Developers are crazy about adding this function.  

$ boosthub --server 0.0.0.0 1234  
Start the server-side boothub service  

$ boosthub --shell 127.0.0.1 1234  
Client shell connection server  

``` 




## Boosthub shell  
### `>> ls`  
`View the file and directory information under the location`  

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

### `>> cd [Folder path]` 
`Switch the current path` 

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

### `>> pwd` 
`View the path at this time`  
```shell 
>> cd /var/www
Now Path: /var/www  
>> cd ../
Now Path: /var  
>> pwd
Now Path: /var 
``` 

### `>> get [File path]` 
`Gets the byte stream of the specified file` 
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

## Why Boosthub? 
### `Why not use FTP?` 


》Of course, you can use the FTP tool, which is just a small personal project built for the fun of coding. It has great shortcomings, but I also want to use my own ideas to make my own satisfactory tools.  
》So, we just think of it as an interesting little toy.
 
### `Network protocol `


》Custom communication protocols over TCP/IP. Custom communication protocols on top of TCP/IP, showcasing does not guarantee your data security, but will certainly do its best.

### `Easy to deploy` 

》Users without experience in program development and shell commands can also quickly deploy and run on the server and operate on their file repositories with remote clients.

### `Just to be clear`  

》It's more like a useful, useless little toy that can also be used when needed.

---

## The project structure  

    src (Source code)
    ├── client (Client shell service)  
    ├── entity (Entity object class)  
    ├── file (File related operations)  
    ├── input (Processing user input)  
    ├── log (Logging tools)  
    ├── tool (Tool inheritance encapsulation)  
    ├── net (Network control layer)  
    ├── protocol (Communication protocol)  
    └── main.cpp   

---

## Developers  

This project is being maintained by only one person, if you can give suggestions or submit your code to make the project better. I would appreciate it.   



## Contact us for suggestions  
Email heizuboriyo@gmail.com  
It is developed and maintained in  `Guilin University of Electronic Technology`, China  



## Versions  

|  version   |  date  | changed content |  
|  ----  | ----  |----|  
| [v0.0.1](https://github.com/gaowanlu/boosthub/releases/tag/v0.0.1)  | 2021/11/26 | Network communication, directory reading, log tools, etc |  
| [v0.1.1](https://github.com/gaowanlu/boosthub/releases/tag/v0.1.1)  | 2022/1/4 | Client send shell command and print response on console. setting ip and port for client and server service |  


