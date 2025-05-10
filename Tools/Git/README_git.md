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

## Repo Structure

Similar to the UNIX filesystem:
- root directory, (typically) consisting of other directories, which may contain files (leaf nodes) with data.
- file metadata is stored in the directory (names) and in the i-nodes that reference file contents (size, type, permissions, etc.)
- each i-node has a unique number identifying the contents of its related file
- many direectory entries may point to a particular i-node (i.e. hard links), but the i-node itself owns the contents stored on the filesystem

Git's internal structure has 2 key differences:
- file contents are represented in **blobs** (leaf nodes in a **tree**)
- blobs are leaf nodes in a **tree** (similar to a directory)
- blobs store no metadata about their content
- blobs are named by computing the SHA1 hash of its size and contents
- blobs (data) are immutable

Consequences of the SHA1 hash:
- verifies that the blob's contents will not change
- the same contents shall always be represented by the same blob, no matter where it appear
- multiple trees referencing the same blob is like hard-linking; the blob won't disappear as long as there is at least one link pointing to it

> 📝 **Note**  
> Blobs are the fundamental unit of git.

## Repo Setup

Initialize a repository
```sh
git init
```

Add a file (stage?)
```sh
git add myfile
```

Commit the changes
```sh
git commit -m "Added myfile"
```

## Git Hashes

Check what hash git will use for a file:
```sh
git hash-object myfile # af5626b4a114abcb82d63db7c8082c3c4756e51b
```

You only need as many characters as are needed to uniquely identify a hash, rather than the entire thing. So for instance if you have a hash `af5626b4a114abcb82d63db7c8082c3c4756e51b`, you can use the first handful of characters in most cases - however few are needed to uniquely identify the object.

See what a hash represents
```sh
git cat-file -t af5626b4a114abcb # blob
```

If it's a blob, see its contents
```sh
git cat-file blob af5626b4a114abcb # "hello, world"
```


// https://jwiegley.github.io/git-from-the-bottom-up/1-Repository/3-blobs-are-stored-in-trees.html



// Git Flow workflow... (separate file? more dev oriented)


References:
* [Git from the Bottom Up](https://jwiegley.github.io/git-from-the-bottom-up/)
* 