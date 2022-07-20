# boosthub

linux applications for lightweight file storage repositories and file transfer tools .

## depoly

### prepare

```bash
sudo apt update 
sudo apt install g++ gcc make cmake git 
sudo apt install glibc-doc manpages-posix-dev 
```

### build

```bash
git clone https://github.com/gaowanlu/boosthub.git  
cd ./boosthub 
cmake . 
make 
sudo make install 
```

It's ok.

```text
...
[100%] Built target boosthub
Install the project...
-- Install configuration: ""
-- Installing: /usr/bin/boosthub
```

### help

```bash
sudo boosthub --help
#view help information
```

## document

[reading the detail to use it.](./doc/README.md)

## peoject structure  

```text
doc      # document
refactor # refactor plan
src      # source code
├── client #client shell service  
├── entity #Entity object class  
├── file #file related operations  
├── input #processing user input  
├── log #logging tools  
├── tool #tool inheritance encapsulation  
├── net #network control layer  
├── protocol #communication protocol  
├── warehouse #server file warehouse layer
├── sworks #node server
└── main.cpp   
```

## developers

This project is being maintained by only one person, if you can give suggestions or submit your code to make the project better. I would appreciate it.  

## contact us

Email heizuboriyo@gmail.com  
It is developed and maintained in  `Guilin University of Electronic Technology`, China  

## versions

|  version   |  date  | changed content |  
|  ----  | ----  |----|  
| [v0.0.1](https://github.com/gaowanlu/boosthub/releases/tag/v0.0.1)  | 2021/11/26 | Network communication, directory reading, log tools, etc |  
| [v0.1.1](https://github.com/gaowanlu/boosthub/releases/tag/v0.1.1)  | 2022/1/4 | Client send shell command and print response on console. setting ip and port for client and server service |  
