# Documentation Generation

## Requirements

You'll need the following software:
- [Sphinx](http://www.sphinx-doc.org/en/master/index.html)

### Ubuntu

You can install the required software on Ubuntu with the following:

```
sudo apt install python3-sphinx
```

The second line can be omitted if you don't intend to build the PDF.

### MacOS

You can install the required software on MacOS with the following:

```
brew install sphinx-doc
```

The second line can be omitted if you don't intend to build the PDF.

## Building the Docs

You can generate the HTML documentation with
```
make
```

You can clean the build files and outputs with

```
make clean
```


