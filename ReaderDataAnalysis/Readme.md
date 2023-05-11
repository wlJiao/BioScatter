# Reader Data Analysis

The folder consists of the overall signal processing flow in Matlab. The required Matlab version is MATLAB R2021b or newer.

## Installing MATLAB

```html
https://ww2.mathworks.cn/products/matlab.html
```

## File Declaration

- `main.m` is the main function.
- `funcReadIQDataInParProcessing.m` is a function for loading the raw sample data from `Reader.grc` program. The raw data is a large binary file, usually with a size of 700M~1G. Thus, to accelerate the loading speed, we use the parallel operation in Matlab.
- `funcNormDivSeg.m` is a function for pre-processing the loaded IQ data, which first produces a complex matrix (IQ matrix). And then it normalizes the amplitude of the signal and removes the offset of the whole signal due to dynamic interference in order to demodulate the accurate pulse width.
- `funcDemodulate.m` is a function for demodulating the pulse interval modulated signal since we modulate the sweat sensor's analog output (IV profile) into the carrier signal. Then this function outputs the demodulated I-V profile.
- `funcCutProfile` is a function for trimming the I-V profile to realize a unified-formatted IV profile matrix. The output IV profile is used for sweat concentration estimation.
- `funcLevelIdentification.m` is a function for identifying the current sweat concentration.