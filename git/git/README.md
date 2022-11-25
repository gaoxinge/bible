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

## tag

```
$ git log --pretty=oneline
$ git tag -a v1.2 -m 'my version 1.2'
$ git tag -a v1.4 6887d6
$ git tag v1.4-1w
$ git tag
$ git tag -l 'v1.4*'
$ git show v1.4-1w
```

```
$ git push origin v1.4
$ git push origin --tags
$ git checkout -b version2 v1.2
```

## branch

```
$ git branch testing
$ git checkout testing
$ git checkout -b testing
$ git log --oneline --decorate
$ git log --oneline --decorate --graph --all
```

```
$ git checkout -b iss53
$ vim index.html
$ git commit -a -m 'added a new footer [issue 53]'

$ git checkout master
$ git checkout -b hotfix
$ vim index.html
$ git commit -a -m 'fixed the broken email address'
$ git checkout master
$ git merge hotfix
$ git branch -d hotfix

$ git checkout iss53
$ vim index.html
$ git commit -a -m 'finished the new footer [issue 53]'
$ git checkout master
$ git merge iss53 # conflict
$ git branch -d iss53
```

```
$ git branch
$ git branch -v
$ git branch --merged
$ git branch --no-merged
$ git branch -d iss53 # merged
$ git branch -D testing # no-merged
```

## reference

- [分支-分支开发工作流](https://git-scm.com/book/zh/v2/Git-%E5%88%86%E6%94%AF-%E5%88%86%E6%94%AF%E5%BC%80%E5%8F%91%E5%B7%A5%E4%BD%9C%E6%B5%81)
- [分支-远程分支](https://git-scm.com/book/zh/v2/Git-%E5%88%86%E6%94%AF-%E8%BF%9C%E7%A8%8B%E5%88%86%E6%94%AF)
- [分布式-分布式工作流程](https://git-scm.com/book/zh/v2/%E5%88%86%E5%B8%83%E5%BC%8F-Git-%E5%88%86%E5%B8%83%E5%BC%8F%E5%B7%A5%E4%BD%9C%E6%B5%81%E7%A8%8B)
- [分布式-向一个项目贡献](https://git-scm.com/book/zh/v2/%E5%88%86%E5%B8%83%E5%BC%8F-Git-%E5%90%91%E4%B8%80%E4%B8%AA%E9%A1%B9%E7%9B%AE%E8%B4%A1%E7%8C%AE)
- [分布式-维护项目](https://git-scm.com/book/zh/v2/%E5%88%86%E5%B8%83%E5%BC%8F-Git-%E7%BB%B4%E6%8A%A4%E9%A1%B9%E7%9B%AE)