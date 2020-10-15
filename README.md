# TTY intrusive Docker image

Build this docker image, run it, it will print a big `HELLO WORLD` to every virtual console you open. This is just annoying and you will not be able to use your console. Just stop it from a XTerm, where it can not bother you.

This shows that a docker container with basic privilege still has access to some features of your system, so be careful when you run a unknown docker image on your computer.

#### Build it :
`docker build -t tty_intrusive:latest ./`

#### Run it :
`docker run -d --name bob tty_intrusive`

#### Kill it :
`docker container kill bob`

#### Bonus :
hijack.c allows you, with root privilege, to hijack a user's tty.
