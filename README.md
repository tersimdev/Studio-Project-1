#git commands


git pull origin master 
#pulls from the master branch
git checkout -b "branchname"
##creates a new branch with branchname

do stuff

git add .
#adds files to be committed
git commit -m "message"
#commits changes to local files
git push origin branchname
#pushes changes to branchname

git checkout master
#switch to master branch, repalce master with branchname to switch to branch

git reset HEAD^
#undoes previous commit

git checkout <file>
#restores file to state in github
