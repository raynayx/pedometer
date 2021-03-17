- take data from xl in bites of 50
- store in array of axes
- filter the data into user xl and gravity xl (parser)
    - low_0_hz is used to low-pass filter signals near 0 Hz
    - low_5_hz is used to low-pass filter signals at or below 5 Hz
    - high_1_hz is used to high-pass filter signals above 1 Hz
- process:
    - dot product to isolate movement in the direction of gravity
    - filter low frequencies from resulting 1D data (low_5_hz)
    - filter high frequencies from previous step(high_1_hz)
- analyze
    - set threshold
    - inititalize steps
        


 March 06,2021
 - Rewrite the filter function to use the Circular Buffer
    - Rewriting the filter function with a Circular Buffer caused accumulating values eventually leading to overflows
    - Hence, the circular Buffer will be limited to the Source of the IMU data and the subsquent will be plain old array