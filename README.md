### Purpose
Calculate the latitude and longtitude of Farallon Island CORS site by utilizing its RINEX observation and navigation files downloaded from NOAA ftp server.

### Source
ftp://geodesy.noaa.gov/cors/rinex/2016/076/farb/

### CORS Site Info
Farallon Island

| Lat | Lng | Elev(m) | X(m) | Y(m) | Z(m) |
| --- | --- | ------- | ---- | ---- | ---- |	
| 37.6972 | -123.0008 | -21.7 | -2658220.5 | -4138072.8 | 4049411.8 |

### Current Result
Those are computed location from first 5 observations of the .o file. The result is actually very bad. Errors are huge. Something must went wrong in the code. Might be because of the sloppy GPS time/week conversion or tropo/iono corrections not yet implemented.

| X(m) | Y(m) | Z(m) |
| ---- | ---- | ---- |
| -2701170.9417 | -4168416.4704 | 3850676.5301
| -2701401.0960 | -4168449.0165 | 3850472.5865
| -2701269.9969 | -4168176.1482 | 3850293.5716
| -2701138.7332 | -4167903.0353 | 3850114.3337
| -2701007.5276 | -4167631.0669 | 3849935.3659 

### TODO
- Troposphere correction
- Ionosphere correction
- Rotated ECEF correction
- More precise GPS time/week calculation.

### Dependencies

[Armadillo](http://arma.sourceforge.net/)

### Ref
[ICD-200](http://www.gps.gov/technical/icwg/ICD-GPS-200C.pdf)

[RINEX 2.11 SPEC](https://igscb.jpl.nasa.gov/igscb/data/format/rinex211.txt)

[RINEX Format Explained](https://emedia.rmit.edu.au/satellite/node/16)

[Example Matlab Code](http://kom.aau.dk/~borre/easy/)