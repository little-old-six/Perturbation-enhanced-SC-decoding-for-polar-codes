# Perturbation-Enhanced SC Decoding for Polar Codes


If you find this algorithm useful, please cite the following paper. Thanks.

Z. Yang, L. Chen, K. Qin, X. Wang, and H. Zhang, “Perturbation-based decoding schemes for long polar codes,” in Proc. 2025 IEEE Int. Symp. Inf. Theory (ISIT), Michigan, USA, Jun. 2025.



Abstract: For polar codes, the bit-flipping strategy can significantly improve performance of its successive cancellation (SC) decoding. However, the gain derived from SC-flip (SCF) decoding diminishes as the codeword length increases. Addressing this issue, this paper proposes a novel hybrid perturbation-based SC (HPSC) decoding. If the initial SC decoding fails, the algorithm will generate multiple SC decoding attempts, each of which introduces stochastic perturbations to the received symbols. By soft information perturbations, the SC decoding can divert from the initial erroneous estimation and converge to the intended one. Our simulation results show that the proposed HPSC decoding consistently yields stable coding gains over various codeword lengths and rates. With the same number of decoding attempts, the HPSC decoding outperforms the thresholded SCF (TSCF) decoding. Moreover, it can achieve a similar performance as the cyclic redundancy check (CRC) aided SC list (CA-SCL) decoding, without any path sorting and expansion requirements. 



Description: These are a set of programs for my research work, called “perturbation-based decoding schemes for long polar codes”.

Folder Obtain_delta: A program for obtaining the number of required g-functions in estimating the information bit u_i.



These algorithms might be confusing. Please read the paper carefully, and if you still do not understand it, feel free to contact me via email address ZhongjunYang at ieee dot org


I will also share the whole C++ codes here soon. Maybe when I have come back from the ISIT-2025.



Please report any bugs to ZhongjunYang at ieee dot org.
