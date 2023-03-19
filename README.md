![Code Extractor Banner](./docs/images/code_extractor_banner_v3.png)

> Tool For Literate Programmer


```bash
md2code 0.1.0

Tool to extract code blocks from markdown (Literate Programming)
Arguments : 
	 --input  : input markdown file path
	 --output : output markdown file path
	 --output : language of code blocks to be extracted
	          : if `lang` option not provided only '```' block will be extracted.
	          : otherwise '```lang' blocks will be extracted
```
## Usage

Example : 

```bash
./bin/main.exe --input src.md --output dest.md --lang python
```

## Dev

### Build

> mingw32-make.exe bin/main.c

### Test

> scripts/test.sh

