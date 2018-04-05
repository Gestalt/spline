# spline

Command line tool to interpolate table based function

## Usage:
```
spline [required] [options]

required:
    [--source|-s]         file source with function points
    [--destination|-d]    file source with arguments to be interpolated
    [--spline]            interpolation algorithm: [Neighbor|Linear|Quadric]
    
options:
    [--output|-o]         output file. Default is <output.txt>
    [--verbose|-v]        be verbose
    [--help|-h]           print help
``` 

## Example:
```
spline -s src.txt --destination dest.txt --spline Quadric -v
``` 
