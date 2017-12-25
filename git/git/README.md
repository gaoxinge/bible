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

## update

```
$ git status
$ git status -s
$ git diff # not staged
$ git diff --staged # staged
$ git diff --cached # staged
```

```
$ touch .gitignore
```

```
$ echo 'My Project' > README 
$ git status # untracked
$ git add README
$ git status # staged
$ git commit -m "readme"
$ git status # committed
```

```
$ vim CONTRIBUTING.md
$ git status # modified
$ git add CONTRIBUTING.md
$ git status # staged
$ git commit -m "contributing"
$ git status # committed
```

```
$ vim CONTRIBUTING.md
$ git status # modified
$ git commit -a -m "contributing"
$ git status # committed 
```

```
$ rm PROJECTS.md
$ git status # deleted
$ git rm PROJECTS.md
$ git status # staged
$ git commit -m "project"
$ git status # committed
```

```
$ git rm --cached PROJECTS.md
$ git status # deleted & untracked
$ git commit -m "project"
$ git status # untracked
```

```
$ git mv README.md README
$ git status # renamed
$ git commit -m "readme"
$ git status # committed
```

## log

```
$ git log
$ git log -2 # 最近两条
$ git log -p # 内容
$ git log --stat # 内容
```

## cancel

```
# 忘记提交forgotten_file
$ git commit -m "initial commit"
$ git add forgotten_file
$ git commit --amend
```

```
# 撤销暂存的CONTRIBUTING.md
$ git add *
$ git reset HEAD CONTRIBUTING.md
```

```
# 取消对CONTRIBUTING.md的修改
$ git checkout -- CONTRIBUTING.md
```

## remote repository

```
$ git clone https://github.com/libgit2/libgit2
$ git push origin master
$ git pull
```