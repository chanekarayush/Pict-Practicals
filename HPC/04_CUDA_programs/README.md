# CUDA Benchmarks

This directory contains CUDA implementations for Vector Addition and Matrix Multiplication.

## Files
- `cuda_benchmarks.ipynb`: A Google Colab compatible notebook containing the full implementation and benchmarking code.

## How to use in Google Colab
1. Upload `cuda_benchmarks.ipynb` to Google Drive or open it directly in [Google Colab](https://colab.research.google.com/).
2. Change the runtime type to **GPU**: `Runtime` -> `Change runtime type` -> `Hardware accelerator` -> `GPU`.
3. Run all cells.

## Benchmarks Included
1. **Vector Addition:** Adds two vectors of ~33 million elements.
2. **Matrix Multiplication:** Multiplies two 512x512 matrices (size kept moderate for CPU comparison).

Both benchmarks compare the execution time of the sequential CPU version vs the parallel CUDA version and verify the results.
