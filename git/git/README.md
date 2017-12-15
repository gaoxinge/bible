## config

```
$ git config --global user.name "John Doe"
$ git config --global user.email johndoe@example.com
$ git cofnig --global core.editor emacs

$ git config --list
$ git config user.name
$ git config user.email
```

## help

```
$ git help config
$ git config --help
```

## git repository

```
$ mkdir mylibgit
$ cd mylibgit
$ git init
$ touch a.c b.c
$ touch LICENSE
$ git add *.c
$ git add LICENSE
$ git commit -m "initial project version"
```

```
# https协议
$ git clone https://github.com/libgit2/libgit2
$ git clone https://github.com/libgit2/libgit2 mylibgit

# ssh协议
$ git clone git@github.com:libgit2/libgit2.git
$ git clone git@github.com:libgit2/libgit2.git mylibgit
```