


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

<div align="center">  

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

</div>  

--- 

## Brief Introduction  
Using Boosthub you can store your file repository on the server side, and you can operate the repository on the client side.    

Boosthub is an extremely simple application that doesn't require other Linux applications to rely on . 
 
--- 

## Quick Start 
###  1. Prepare  
```  
$ sudo apt update 
$ sudo apt install g++ gcc make cmake git 
$ sudo apt install glibc-doc manpages-posix-dev 
``` 

### 2. Get Boosthub
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
### 3. Use Boosthub 
```
$ boosthub -h
``` 

---


## Using the details  
### `$ls`  
> View the file and directory information under the location  


```shell
$ boosthub ls
```
```shell
Folder Path: / File Sum: 26 
Fd: 83406 Name: . Type:d 
Fd: 83406 Name: .. Type:d 
Fd: 83460 Name: hub Type:d 
Fd: 83461 Name: safe Type:d 
Fd: 83462 Name: boosthub Type:d 
```

---

## Why Boosthub? 
### `Why not use FTP?`

```code
You of course take advantage of FTP tools, this is just a personal little project, built for the fun of coding. With FTP it has huge disadvantages, but I also want to use my own ideas to make their own satisfactory tools.
```  
### `Network protocol `

```code
Custom communication protocols over TCP/IP. Custom communication protocols on top of TCP/IP, showcasing does not guarantee your data security, but will certainly do its best.
```
### `Easy to deploy` 
```code
Users without experience in program development and shell commands can also quickly deploy and run on the server and operate on their file repositories with remote clients.
```
### `Just to be clear`  
```code
It's more like a useful, useless little toy that can also be used when needed.
```

---

## Developers  

This project is being maintained by only one person, if you can give suggestions or submit your code to make the project better. I would appreciate it.   

---

## Contact us for suggestions  
Email heizuboriyo@gmail.com  
It is developed and maintained in  `Guilin University of Electronic Technology`, China  

---

## Versions  

|  version   |  date  | changed content |  
|  ----  | ----  |----|  
| [v0.0.1]( )  | 2021/11/26 | Network communication, directory reading, log tools, etc |  



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/gaowanlu/boosthub.svg?style=for-the-badge
[contributors-url]: https://github.com/gaowanlu/boosthub/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/gaowanlu/boosthub.svg?style=for-the-badge
[forks-url]: https://github.com/gaowanlu/boosthub/network/members
[stars-shield]: https://img.shields.io/github/stars/gaowanlu/boosthub.svg?style=for-the-badge
[stars-url]: https://github.com/gaowanlu/boosthub/stargazers
[issues-shield]: https://img.shields.io/github/issues/gaowanlu/boosthub.svg?style=for-the-badge
[issues-url]: https://github.com/gaowanlu/boosthub/issues
[license-shield]: https://img.shields.io/github/license/gaowanlu/boosthub.svg?style=for-the-badge
[license-url]: https://github.com/gaowanlu/boosthub/blob/master/LICENSE.txt