# Git

Decentralized de-facto version control system (VCS).

## Keywords

| Term | Meaning |
| ---- | ------- |
| working tree      | directory on the filesystem with an associated repository, usually indicated by a `.git` folder. |
| commit            | snapshot of the working tree at some point in time. at a commit's creation time, the state of `HEAD` becomes its parent. a series of commits creates the notion of a "revision history". |
| repository (repo) | collection of commits, an archive of what the project's working tree. defines `HEAD` and contains a set of branches and tags to identify certain commits by name. |
| index             | aka the staging area. changes are registered here before being committed to the working tree. |
| branch            | aka a reference. a name for a commit. its parentage defines its history ("branch of development") |
| tag               | a name for a commit, but it always names the same commit, and can have its own description text. |
| master/main       | the default branch of a repository. git's default was `master` until 2020, it is now `main`. commonly reserved for releases. sometimes called `trunk` in older repos or by folks who started with older VCSs. |
| develop           | in the "Git Flow" workflow, the branch used for feature integration in the Git Flow workflow
| `HEAD`            | used by your repo to define what's currently checked out:<br>* if you check out a branch, `HEAD` symbolically refers to that branch, indicating the branch name that should be updated after the next commit operation.<br>* if you check out a specific commit, `HEAD` refers ONLY to that commit. known as a `detatched HEAD`. |

Typical workflow:
- create/clone repository
- create or switch to a branch where you will do your work
- make your changes, add them to the index
- commit your changes, with a comment summarizing your work since the last commit
- (optional) push your changes to the remote repository (if applicable)


// Git Flow workflow... (separate file? more dev oriented)


References:
* [Git from the Bottom Up](https://jwiegley.github.io/git-from-the-bottom-up/)
* 