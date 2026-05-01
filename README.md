# Perturbation-Enhanced SC Decoding for Polar Codes


These algorithms are for my latest work. If you find these algorithms useful, please cite the following paper. Thanks.


- Z. Yang, L. Chen, K. Qin, X. Wang, and H. Zhang “Improved Successive Cancellation Decoding of Polar Codes Through Perturbing A Posteriori LLRs and Its Theoretical Insights,” IEEE Transactions on Communications, vol. 74, pp. 5489–5503, 2026.



Earlier versions of the above paper were presented in part at the 2025 IEEE ISIT [1] and the 2025 IEEE ITW [2]. 


- [1] Z. Yang, L. Chen, K. Qin, X. Wang, and H. Zhang, “Perturbation-based decoding schemes for long polar codes,” in Proc. 2025 IEEE Int. Symp. Inf. Theory (ISIT), Ann Arbor, MI, USA, Jun. 2025.

- [2] Z. Yang, L. Chen, K. Qin, X. Wang, and H. Zhang, “Improved successive cancellation decoding of polar codes through perturbing a posteriori LLRs,” in Proc. 2025 IEEE Inf. Theory Workshop (ITW), Sydney, Australia, Sep. 2025.


# Abstract: 
For polar codes, perturbing received information can enhance the successive cancellation (SC) decoding performance. This is an effective approach for realizing low-latency yet
high performance for long polar codes, since all the perturbation-enhanced SC (PSC) decoding can be performed in parallel. This paper provides theoretical insights into soft information
perturbation, revealing that the PSC decoding can be equivalently
interpreted as perturbing the a posteriori log-likelihood ratios
(LLRs) of information bits. Such a revelation leads to the
design of an improved PSC (IPSC) decoding that yields a
lower perturbation complexity. By better utilizing the decoding
a posteriori LLRs, a set of possibly erroneous estimations can be
formed and further perturbed, resulting in the proposed hybrid
PSC (HPSC) decoding. During each new SC decoding attempt,
it takes turns to flip the first erroneous bit by introducing a
biased perturbation, while the subsequent erroneous estimations
are corrected through random perturbations. Our simulation
results validate that, for various codeword lengths and rates, the
proposed IPSC decoding can achieve a similar performance as
the conventional PSC decoding, but yield a significantly reduced
perturbation complexity. With the same number of decoding
attempts, the proposed HPSC decoding outperforms several state-of-the-art SC-based decoding, such as the thresholded SC-flip
(TSCF) decoding and the dynamic SC-flip (DSCF) decoding.




# Description: 
These are a set of programs for my research work, called “perturbation-based decoding schemes for long polar codes”.

- **Function-Obtain_delta:** A program for obtaining the number of required g-functions in estimating the information bit u_i.

- **Algorithm-Random Perturbation-based SC decoding:** It implements the random perturbation-based SC (RPSC) decoding proposed in our recent work [1]. Note that the same algorithm is also referred to as the perturbation-based SC (PSC) decoding in ITW 2025 [2]. More information, please read the readme-RPSC.


# Contact & Feedback:
These algorithms might be confusing. Please read the paper carefully, and if you still do not understand it, feel free to contact me via email address ZhongjunYang at ieee dot org


- I will also share the whole codes here soon. Maybe when I have received my PhD in 2026.



- Please report any bugs to ZhongjunYang at ieee dot org.
