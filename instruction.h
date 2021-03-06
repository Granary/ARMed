#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_


#define CAT_UNCONDITIONAL   1
#define CAT_DATAPROC        2
#define CAT_LOADSTORE1      3
#define CAT_LOADSTORE2      4
#define CAT_BRANCH          5
#define CAT_SVC             6
#define CAT_UNDEFINED       7
#define CAT_NUMBER          6

#define DP_REGISTER 		1
#define DP_REGISTERSR		2
#define DP_MISC				3
#define DP_HWMMA			4
#define DP_MULTIPLYMA		5
#define DP_SP				6
#define DP_EXTRALS			7
#define DP_EXTRALSUP		8
#define DP_IMM				9
#define DP_IMMLD			10
#define DP_IMMHILD			11
#define DP_MSRIMM			12
#define DP_UNDEFINED		13
#define DP_NUMBER			14

enum {
    NULL_kind,
    IMMED_INTEGER_kind,
    IMMED_FLOAT_kind,
    PC_kind,
    REG_kind,
    BASE_DISP_kind,
    LAST_kind,
};

/* Enum to store the type of the instruction */
enum
{
  INSTR_TYPE_UNDECODED = 0,

  INSTR_TYPE_DATA_PROCESSING_AND_ELS, //and extra load/store instructions
  INSTR_TYPE_DATA_PROCESSING_IMM,
  INSTR_TYPE_LOAD_STORE1,
  INSTR_TYPE_LOAD_STORE2_AND_MEDIA,
  INSTR_TYPE_LOAD_STORE_MULTIPLE,
  INSTR_TYPE_BRANCH,
  INSTR_TYPE_COPROCESSOR_DATA_MOVEMENT,
  INSTR_TYPE_ADVANCED_COPROCESSOR_AND_SYSCALL,

  INSTR_TYPE_INVALID
};

enum
{
  MASK_UNDEFINED = 0,

  MASK_WRITE_NSCVQ_FLAGS,
  MASK_WRITE_G_FLAG,
  MASK_WRITE_ALL,

  MASK_INVALID
};

enum
{
  COND_EQUAL = 0,
  COND_NOT_EQUAL,
  COND_CARRY_SET,
  COND_CARRY_CLEAR,
  COND_MINUS,
  COND_PLUS,
  COND_OVERFLOW,
  COND_NO_OVERFLOW,
  COND_HIGHER,
  COND_LOWER_OR_SAME,
  COND_SIGNED_GREATER_THAN_OR_EQUAL,
  COND_SIGNED_LESS_THAN,
  COND_SIGNED_GREATER_THAN,
  COND_SIGNED_LESS_THAN_OR_EQUAL,
  COND_ALWAYS,

  COND_INVALID
};

/** Opcode constants for use in the instr_t data structure. */
enum {
/*   0 */     OP_INVALID,  /* NULL, */ /**< INVALID opcode */
/*   1 */     OP_UNDECODED,  /* NULL, */ /**< UNDECODED opcode */
/*   2 */     OP_CONTD,    /* NULL, */ /**< CONTD opcode */
/*   3 */     OP_LABEL,    /* NULL, */ /**< LABEL opcode */

/*   4 */     OP_adc_imm,
/*   5 */     OP_adc_reg,
/*   6 */     OP_adc_rsr,
/*   7 */     OP_add_imm,
/*   8 */     OP_add_reg,
/*   9 */     OP_add_rsr,
/*   10 */     OP_add_sp_imm,
/*   11 */     OP_add_sp_reg,
/*   12 */     OP_adr,
/*   13 */     OP_and_imm,
/*   14 */     OP_and_reg,
/*   15 */     OP_and_rsr,
/*   16 */     OP_asr_imm,
/*   17 */     OP_asr_reg,
/*   18 */     OP_b,
/*   19 */     OP_bfc,
/*   20 */     OP_bfi,
/*   21 */     OP_bic_imm,
/*   22 */     OP_bic_reg,
/*   23 */     OP_bic_rsr,
/*   24 */     OP_bkpt,
/*   25 */     OP_bl,
/*   26 */     OP_blx_imm,
/*   27 */     OP_blx_reg,
/*   28 */     OP_bx,
/*   29 */     OP_bxj,
/*   30 */     OP_cbnz,
/*   31 */     op_cbz,
/*   32 */     OP_cdp,
/*   33 */     OP_cdp2,
/*   34 */     OP_clrex,
/*   35 */     OP_clz,
/*   36 */     OP_cmn_imm,
/*   37 */     OP_cmn_reg,
/*   38 */     OP_cmn_rsr,
/*   39 */     OP_cmp_imm,
/*   40 */     OP_cmp_reg,
/*   41 */     OP_cmp_rsr,
/*   42 */     OP_cps,
/*   43 */     OP_dbg,
/*   44 */     OP_dmb,
/*   45 */     OP_dsb,
/*   46 */     OP_eor_imm,
/*   47 */     OP_eor_reg,
/*   48 */     OP_eor_rsr,
/*   49 */     OP_isb,
/*   50 */     OP_it,
/*   51 */     OP_ldc_imm,
/*   52 */     OP_ldc2_imm,
/*   53 */     OP_ldc_lit,
/*   54 */     OP_ldc2_lit,
/*   55 */     OP_ldm,
/*   56 */     OP_ldmia,
/*   57 */     OP_ldmfd,
/*   58 */     OP_ldmda,
/*   59 */     OP_ldmfa,
/*   60 */     OP_ldmdb,
/*   61 */     OP_ldmea,
/*   62 */     OP_ldmib,
/*   63 */     OP_ldmed,
/*   64 */     OP_ldr_imm,
/*   65 */     OP_ldr_lit,
/*   66 */     OP_ldr_reg,
/*   67 */     OP_ldrb_imm,
/*   68 */     OP_ldrb_lit,
/*   69 */     OP_ldrb_reg,
/*   70 */     OP_ldrbt,
/*   71 */     OP_ldrd_imm,
/*   72 */     OP_ldrd_lit,
/*   73 */     OP_ldrd_reg,
/*   74 */     OP_ldrex,
/*   75 */     OP_ldrexb,
/*   76 */     OP_ldrexd,
/*   77 */     OP_ldrexh,
/*   78 */     OP_ldrh_imm,
/*   79 */     OP_ldrh_lit,
/*   80 */     OP_ldrh_reg,
/*   81 */     OP_ldrht,
/*   82 */     OP_ldrsb_imm,
/*   83 */     OP_ldrsb_lit,
/*   84 */     OP_ldrsb_reg,
/*   85 */     OP_ldrsbt,
/*   86 */     OP_ldrsh_imm,
/*   87 */     OP_ldrsh_lit,
/*   88 */     OP_ldrsh_reg,
/*   89 */     OP_ldrsht,
/*   90 */     OP_ldrt,
/*   91 */     OP_lsl_imm,
/*   92 */     OP_lsl_reg,
/*   93 */     OP_lsr_imm,
/*   94 */     OP_lsr_reg,
/*   95 */     OP_mcr,
/*   96 */     OP_mcr2,
/*   97 */     OP_mcrr,
/*   98 */     OP_mcrr2,
/*   99 */     OP_mla,
/*   100 */     OP_mls,
/*   101 */     OP_mov_imm,
/*   102 */     OP_mov_reg,
/*   103 */     OP_movt,
/*   104 */     OP_mrc,
/*   105 */     OP_mrc2,
/*   106 */     OP_mrrc,
/*   107 */     OP_mrrc2,
/*   108 */     OP_mrs,
/*   109 */     OP_msr_imm,
/*   110 */     OP_msr_reg,
/*   111 */     OP_mul,
/*   112 */     OP_mvn_imm,
/*   113 */     OP_mvn_reg,
/*   114 */     OP_mvn_rsr,
/*   115 */     OP_nop,
/*   116 */     OP_orn_imm,
/*   117 */     OP_orn_reg,
/*   118 */     OP_orr_imm,
/*   119 */     OP_orr_reg,
/*   120 */     OP_orr_rsr,
/*   121 */     OP_pkh,
/*   122 */     OP_pld_imm,
/*   123 */     OP_pldw_imm,
/*   124 */     OP_pld_lit,
/*   125 */     OP_pldw_lit,
/*   126 */     OP_pld_reg,
/*   127 */     OP_pldw_reg,
/*   128 */     OP_pli_imm,
/*   129 */     OP_pli_lit,
/*   130 */     OP_pli_reg,
/*   131 */     OP_pop,
/*   132 */     OP_push,
/*   133 */     OP_qadd,
/*   134 */     OP_qadd16,
/*   135 */     OP_qadd8,
/*   136 */     OP_qasx,
/*   137 */     OP_qdadd,
/*   138 */     OP_qdsub,
/*   139 */     OP_qsax,
/*   140 */     OP_qsub,
/*   141 */     OP_qsub16,
/*   142 */     OP_qsub8,
/*   143 */     OP_rbit,
/*   144 */     OP_rev,
/*   145 */     OP_rev16,
/*   146 */     OP_revsh,
/*   147 */     OP_rfe,
/*   148 */     OP_ror_imm,
/*   149 */     OP_ror_reg,
/*   150 */     OP_rrx,
/*   151 */     OP_rsb_imm,
/*   152 */     OP_rsb_reg,
/*   153 */     OP_rsb_rsr,
/*   154 */     OP_rsc_imm,
/*   155 */     OP_rsc_reg,
/*   156 */     OP_rsc_rsr,
/*   157 */     OP_sadd16,
/*   158 */     OP_sadd8,
/*   159 */     OP_sasx,
/*   160 */     OP_sbc_imm,
/*   161 */     OP_sbc_reg,
/*   162 */     OP_sbc_rsr,
/*   163 */     OP_sbfx,
/*   164 */     OP_sdiv,
/*   165 */     OP_sel,
/*   166 */     OP_setend,
/*   167 */     OP_sev,
/*   168 */     OP_shadd16,
/*   169 */     OP_shadd8,
/*   170 */     OP_shsax,
/*   171 */     OP_shsub16,
/*   172 */     OP_shsub8,
/*   173 */     OP_smlabb,
/*   174 */     OP_smlabt,
/*   175 */     OP_smlatb,
/*   176 */     OP_smlatt,
/*   177 */     OP_smlad,
/*   178 */     OP_smlal,
/*   179 */     OP_smlalbb,
/*   180 */     OP_smlalbt,
/*   181 */     OP_smlaltb,
/*   182 */     OP_smlaltt,
/*   183 */     OP_smlald,
/*   184 */     OP_smlawb,
/*   185 */     OP_smlawt,
/*   186 */     OP_smlsd,
/*   187 */     OP_smlsld,
/*   188 */     OP_smmla,
/*   189 */     OP_smmls,
/*   190 */     OP_smmul,
/*   191 */     OP_smuad,
/*   192 */     OP_smulbb,
/*   193 */     OP_smulbt,
/*   194 */     OP_smultb,
/*   195 */     OP_smultt,
/*   196 */     OP_smull,
/*   197 */     OP_smulwb,
/*   198 */     OP_smulwt,
/*   199 */     OP_smusd,
/*   200 */     OP_srs,
/*   201 */     OP_ssat,
/*   202 */     OP_ssat16,
/*   203 */     OP_ssax,
/*   204 */     OP_ssub16,
/*   205 */     OP_ssub8,
/*   206 */     OP_stc,
/*   207 */     OP_stc2,
/*   208 */     OP_stm,
/*   209 */     OP_stmia,
/*   210 */     OP_stmea,
/*   211 */     OP_stmda,
/*   212 */     OP_stmed,
/*   213 */     OP_stmdb,
/*   214 */     OP_stmfd,
/*   215 */     OP_stmib,
/*   216 */     OP_stmfa,
/*   217 */     OP_str_imm,
/*   218 */     OP_str_reg,
/*   219 */     OP_strb_imm,
/*   220 */     OP_strb_reg,
/*   221 */     OP_strbt,
/*   222 */     OP_strd_imm,
/*   223 */     OP_strd_reg,
/*   224 */     OP_strex,
/*   225 */     OP_strexb,
/*   226 */     OP_strexd,
/*   227 */     OP_strexh,
/*   228 */     OP_strh_imm,
/*   229 */     OP_strh_reg,
/*   230 */     OP_strht,
/*   231 */     OP_strt,
/*   232 */     OP_sub_imm,
/*   233 */     OP_sub_reg,
/*   234 */     OP_sub_rsr,
/*   235 */     OP_sub_sp_imm,
/*   236 */     OP_sub_sp_reg,
/*   237 */     OP_subs,
/*   238 */     OP_svc,
/*   239 */     OP_swp,
/*   240 */     OP_swpb,
/*   241 */     OP_sxtab,
/*   242 */     OP_sxtab16,
/*   243 */     OP_sxtah,
/*   244 */     OP_tbb,
/*   245 */     OP_tbh,
/*   246 */     OP_teq_imm,
/*   247 */     OP_teq_reg,
/*   248 */     OP_teq_rsr,
/*   249 */     OP_tst_imm,
/*   250 */     OP_tst_reg,
/*   251 */     OP_tst_rsr,
/*   252 */     OP_uadd16,
/*   253 */     OP_uadd8,
/*   254 */     OP_uasx,
/*   255 */     OP_ubfx,
/*   256 */     OP_udiv,
/*   257 */     OP_uhadd16,
/*   258 */     OP_uhadd8,
/*   259 */     OP_uhsax,
/*   260 */     OP_uhsub16,
/*   261 */     OP_uhsub8,
/*   262 */     OP_umaal,
/*   263 */     OP_umlal,
/*   264 */     OP_umull,
/*   265 */     OP_uqadd16,
/*   266 */     OP_uqadd8,
/*   267 */     OP_uqasx,
/*   268 */     OP_uqsax,
/*   269 */     OP_usub16,
/*   270 */     OP_usub8,
/*   271 */     OP_usad8,
/*   272 */     OP_usada8,
/*   273 */     OP_usat,
/*   274 */     OP_usat16,
/*   275 */     OP_usax,
/*   276 */     OP_uxtab,
/*   277 */     OP_uxtab16,
/*   278 */     OP_uxtah,
/*   279 */     OP_uxtb,
/*   280 */     OP_uxtb16,
/*   281 */     OP_uxth,
/*   282 */     OP_vaba,
/*   283 */     OP_vabal_int,
/*   284 */     OP_vabd_int,
/*   285 */     OP_vabd_flt,
/*   286 */     OP_vabs,
/*   287 */     OP_vacge,
/*   288 */     OP_vacgt,
/*   289 */     OP_vacle,
/*   290 */     OP_vaclt,
/*   291 */     OP_vadd_int,
/*   292 */     OP_vadd_flt,
/*   293 */     OP_vaddhn,
/*   294 */     OP_vaddl,
/*   295 */     OP_vaddw,
/*   296 */     OP_vand_imm,
/*   297 */     OP_vand_reg,
/*   298 */     OP_vbic_imm,
/*   299 */     OP_vbic_reg,
/*   300 */     OP_vbif,
/*   301 */     OP_vbsl,
/*   302 */     OP_vceq_reg,
/*   303 */     OP_vceq_imm,
/*   304 */     OP_vcge_reg,
/*   305 */     OP_vcge_imm,
/*   306 */     OP_vcgt_reg,
/*   307 */     OP_vcgt_imm,
/*   308 */     OP_vcle_reg,
/*   309 */     OP_vcle_imm,
/*   310 */     OP_vcls,
/*   311 */     OP_vclt_reg,
/*   312 */     OP_vclt_imm,
/*   313 */     OP_vclz,
/*   314 */     OP_vcmp,
/*   315 */     OP_vcmpe,
/*   316 */     OP_vcnt,
/*   317 */     OP_vcvt_flt_int_simd,
/*   318 */     OP_vcvt_flt_int_vfp,
/*   319 */     OP_vcvtr_flt_int_vfp,
/*   320 */     OP_vcvt_flt_fip_simd,
/*   321 */     OP_vcvt_dp_sp,
/*   322 */     OP_vcvt_hp_sp_simd,
/*   323 */     OP_vcvtb_hp_sp_vfp,
/*   324 */     OP_vcvtt_hp_sp_vfp,
/*   325 */     OP_vdiv,
/*   326 */     OP_vdup_scl,
/*   327 */     OP_vdup_reg,
/*   328 */     OP_veor,
/*   329 */     OP_vext,
/*   330 */     OP_vhadd,
/*   331 */     OP_vhsub,
/*   332 */     OP_vld1_mse,
/*   333 */     OP_vld1_se1,
/*   334 */     OP_vld1_sea,
/*   335 */     OP_vld2_m2es,
/*   336 */     OP_vld2_s2e1,
/*   337 */     OP_vld2_s2ea,
/*   338 */     OP_vld3_m3s,
/*   339 */     OP_vld3_se1,
/*   340 */     OP_vld3_sea,
/*   341 */     OP_vld4_m4es,
/*   342 */     OP_vld4_se1,
/*   343 */     OP_vld4_s4ea,
/*   344 */     OP_vldm,
/*   345 */     OP_vldr,
/*   346 */     OP_vmax_int,
/*   347 */     OP_vmin_int,
/*   348 */     OP_vmax_flt,
/*   349 */     OP_vmin_flt,
/*   350 */     OP_vmla_int,
/*   351 */     OP_vmlal_int,
/*   352 */     OP_vmls_int,
/*   353 */     OP_vmlsl_int,
/*   354 */     OP_vmla_flt,
/*   355 */     OP_vmls_flt,
/*   356 */     OP_vmla_scl,
/*   357 */     OP_vmlal_scl,
/*   358 */     OP_vmls_scl,
/*   359 */     OP_vmlsl_scl,
/*   360 */     OP_vmov_imm,
/*   361 */     OP_vmov_reg,
/*   362 */     OP_vmov_reg_scl,
/*   363 */     OP_vmov_scl_reg,
/*   364 */     OP_vmov_reg_sp,
/*   365 */     OP_vmov_2reg_2sp,
/*   366 */     OP_vmov_2reg_2dp,
/*   367 */     OP_vmovl,
/*   368 */     OP_vmovn,
/*   369 */     OP_vmrs,
/*   370 */     OP_vmsr,
/*   371 */     OP_vmul_int,
/*   372 */     OP_vmull_int,
/*   373 */     OP_vmul_flp,
/*   374 */     OP_vmul_scl,
/*   375 */     OP_vmull_scl,
/*   376 */     OP_vmvn_imm,
/*   377 */     OP_vmvn_reg,
/*   378 */     OP_vneg,
/*   379 */     OP_vnmla,
/*   380 */     OP_vnmls,
/*   381 */     OP_vnmul,
/*   382 */     OP_vorn_imm,
/*   383 */     OP_vorn_reg,
/*   384 */     OP_vorr_imm,
/*   385 */     OP_vorr_reg,
/*   386 */     OP_vpadal,
/*   387 */     OP_vpadd_int,
/*   388 */     OP_vpadd_flp,
/*   389 */     OP_vpaddl,
/*   390 */     OP_vpmax_int,
/*   391 */     OP_vpmin_int,
/*   392 */     OP_vpmax_flp,
/*   393 */     OP_vpmin_flp,
/*   394 */     OP_vpop,
/*   395 */     OP_vpush,
/*   396 */     OP_vqabs,
/*   397 */     OP_vqadd,
/*   398 */     OP_vqdmlal,
/*   399 */     OP_vqdmlsl,
/*   400 */     OP_vqdmulh,
/*   401 */     OP_vqdmull,
/*   402 */     OP_vqdmovn,
/*   403 */     OP_vqdmovun,
/*   404 */     OP_vqneq,
/*   405 */     OP_vqrdmulh,
/*   406 */     OP_vqrshl,
/*   407 */     OP_vqrshrn,
/*   408 */     OP_vqrshrun,
/*   409 */     OP_vqshl_reg,
/*   410 */     OP_vqshl_imm,
/*   411 */     OP_vqshlu_imm,
/*   412 */     OP_vqshrn,
/*   413 */     OP_vqshrun,
/*   414 */     OP_vqsub,
/*   415 */     OP_vqraddhn,
/*   416 */     OP_vqrecpe,
/*   417 */     OP_vqrecps,
/*   418 */     OP_vrev16,
/*   419 */     OP_vrev32,
/*   420 */     OP_vrev64,
/*   421 */     OP_vrhadd,
/*   422 */     OP_vrshl,
/*   423 */     OP_vrshr,
/*   424 */     OP_vrshrn,
/*   425 */     OP_vrsqrte,
/*   426 */     OP_vrsqrts,
/*   427 */     OP_vrsra,
/*   428 */     OP_vrsubhn,
/*   429 */     OP_vshl_imm,
/*   430 */     OP_vshl_reg,
/*   431 */     OP_vshll,
/*   432 */     OP_vshr,
/*   433 */     OP_vshrn,
/*   434 */     OP_vsli,
/*   435 */     OP_vsqrt,
/*   436 */     OP_vsra,
/*   437 */     OP_vsri,
/*   438 */     OP_vst1_mse,
/*   439 */     OP_vst1_se1,
/*   440 */     OP_vst2_m2e,
/*   441 */     OP_vst2_s2e1,
/*   442 */     OP_vst3_m3es,
/*   443 */     OP_vst3_s3e1,
/*   444 */     OP_vst4_m4es,
/*   445 */     OP_vst4_s4e1,
/*   446 */     OP_vstm,
/*   447 */     OP_vstr,
/*   448 */     OP_vsub_int,
/*   449 */     OP_vsub_flp,
/*   450 */     OP_vsubhn,
/*   451 */     OP_vsubl,
/*   452 */     OP_vsubw,
/*   453 */     OP_vswp,
/*   454 */     OP_vtbl,
/*   455 */     OP_vtbx,
/*   456 */     OP_vtrn,
/*   457 */     OP_vtst,
/*   458 */     OP_vuzp,
/*   459 */     OP_vzip,
/*   460 */     OP_wfe,
/*   461 */     OP_wfi,
/*   462 */     OP_yield,

/*   463 */     OP_AFTER_LAST_ARM, //SJF Sentinel value to border ARM opcodes

//SJF Add the thumb instrs here. Just duplicate the ARM equivs

/*   464 */     OP_T_add_reg,
/*   465 */     OP_T_adc_reg,
/*   466 */     OP_T_add_low_reg,
/*   467 */     OP_T_add_high_reg,
/*   468 */     OP_T_add_sp_imm,
/*   469 */     OP_T_add_imm_3,
/*   470 */     OP_T_add_imm_8,
/*   471 */     OP_T_and_reg,
/*   472 */     OP_T_asr_imm,
/*   473 */     OP_T_asr_reg,
/*   474 */     OP_T_b,
/*   475 */     OP_T_bic_reg,
/*   476 */     OP_T_bkpt,
/*   477 */     OP_T_blx_ref,
/*   478 */     OP_T_bx,
/*   479 */     OP_T_cbnz,
/*   480 */     OP_T_cbnz_2,
/*   481 */     OP_T_cbz,
/*   482 */     OP_T_cbz_2,
/*   483 */     OP_T_cmn_reg,
/*   484 */     OP_T_cmp_high_reg,
/*   485 */     OP_T_cmp_imm,
/*   486 */     OP_T_cmp_reg,
/*   487 */     OP_T_cps,
/*   488 */     OP_T_eor_reg,
/*   489 */     OP_T_it,
/*   490 */     OP_T_ldrb_imm,
/*   491 */     OP_T_ldrb_reg,
/*   492 */     OP_T_ldrh_imm,
/*   493 */     OP_T_ldrh_reg,
/*   494 */     OP_T_ldrsb_reg,
/*   495 */     OP_T_ldrsh_reg,
/*   496 */     OP_T_ldr_imm,
/*   497 */     OP_T_ldr_reg,
/*   498 */     OP_T_lsl_imm,
/*   499 */     OP_T_lsl_reg,
/*   500 */     OP_T_lsr_imm,
/*   501 */     OP_T_lsr_reg,
/*   502 */     OP_T_mov_imm,
/*   503 */     OP_T_mov_high_reg,
/*   504 */     OP_T_mov_low_reg,
/*   505 */     OP_T_mvn_reg,
/*   506 */     OP_T_mul,
/*   507 */     OP_T_nop,
/*   508 */     OP_T_orr_reg,
/*   509 */     OP_T_pop,
/*   510 */     OP_T_push,
/*   511 */     OP_T_rev,
/*   512 */     OP_T_rev16,
/*   513 */     OP_T_revsh,
/*   514 */     OP_T_ror_reg,
/*   515 */     OP_T_rsb_imm,
/*   516 */     OP_T_sbc_reg,
/*   517 */     OP_T_setend,
/*   518 */     OP_T_sev,
/*   519 */     OP_T_str_imm,
/*   520 */     OP_T_str_reg,
/*   521 */     OP_T_str_sp,
/*   522 */     OP_T_strb_imm,
/*   523 */     OP_T_strb_reg,
/*   524 */     OP_T_strh_imm,
/*   525 */     OP_T_strh_reg,
/*   526 */     OP_T_sub_sp_imm,
/*   527 */     OP_T_sub_imm_8,
/*   528 */     OP_T_sub_reg,
/*   529 */     OP_T_sub_imm_3,
/*   530 */     OP_T_svc,
/*   531 */     OP_T_sxth,
/*   532 */     OP_T_sxtb,
/*   533 */     OP_T_tst_reg,
/*   534 */     OP_T_uxtb,
/*   535 */     OP_T_uxth,
/*   536 */     OP_T_wfe,
/*   537 */     OP_T_wfi,
/*   538 */     OP_T_yield,
/*   539 */     OP_T_32_and_imm,
/*   540 */     OP_T_32_tst_imm,
/*   541 */     OP_T_32_bic_imm,
/*   542 */     OP_T_32_orr_imm,
/*   543 */     OP_T_32_mov_imm,
/*   544 */     OP_T_32_orn_imm,
/*   545 */     OP_T_32_mvn_imm,
/*   546 */     OP_T_32_eor_imm,
/*   547 */     OP_T_32_teq_imm,
/*   548 */     OP_T_32_add_imm,
/*   549 */     OP_T_32_cmn_imm,
/*   550 */     OP_T_32_adc_imm,
/*   551 */     OP_T_32_sbc_imm,
/*   552 */     OP_T_32_sub_imm,
/*   553 */     OP_T_32_cmp_imm,
/*   554 */     OP_T_32_rsb_imm,
/*   555 */     OP_T_32_add_wide,
/*   556 */     OP_T_32_adr,
/*   557 */     OP_T_32_mov_wide,
/*   558 */     OP_T_32_adr_2,
/*   559 */     OP_T_32_movt_top,
/*   560 */     OP_T_32_ssat,
/*   561 */     OP_T_32_ssat16,
/*   562 */     OP_T_32_sbfx,
/*   563 */     OP_T_32_bfi,
/*   564 */     OP_T_32_bfc,
/*   565 */     OP_T_32_usat16,
/*   566 */     OP_T_32_ubfx,
/*   567 */     OP_T_32_b,
/*   568 */     OP_T_32_msr_reg_app,
/*   569 */     OP_T_32_msr_reg_sys,
/*   570 */     OP_T_32_bxj,
/*   571 */     OP_T_32_subs,
/*   572 */     OP_T_32_mrs,
/*   573 */     OP_T_32_smc,
/*   574 */     OP_T_32_b_2,
/*   575 */     OP_T_32_blx_imm,
/*   576 */     OP_T_32_bl,
/*   577 */     OP_T_32_cps,
/*   578 */     OP_T_32_nop,
/*   579 */     OP_T_32_yield,
/*   580 */     OP_T_32_wfe,
/*   581 */     OP_T_32_wfi,
/*   582 */     OP_T_32_sev,
/*   583 */     OP_T_32_dbg,
/*   584 */     OP_T_32_enterx,
/*   585 */     OP_T_32_leavex,
/*   586 */     OP_T_32_clrex,
/*   587 */     OP_T_32_dsb,
/*   588 */     OP_T_32_dmb,
/*   589 */     OP_T_32_isb,
/*   590 */     OP_T_32_srs,
/*   591 */     OP_T_32_rfe,
/*   592 */     OP_T_32_stm,
/*   593 */     OP_T_32_stmia,
/*   594 */     OP_T_32_stmea,
/*   595 */     OP_T_32_ldm,
/*   596 */     OP_T_32_ldmia,
/*   597 */     OP_T_32_ldmfd,
/*   598 */     OP_T_32_pop,
/*   599 */     OP_T_32_stmdb,
/*   600 */     OP_T_32_stmfd,
/*   601 */     OP_T_32_push,
/*   602 */     OP_T_32_ldmdb,
/*   603 */     OP_T_32_ldmea,
/*   604 */     OP_T_32_strex,
/*   605 */     OP_T_32_ldrex,
/*   606 */     OP_T_32_strd_imm,
/*   607 */     OP_T_32_ldrd_imm,
/*   608 */     OP_T_32_ldrd_lit,
/*   609 */     OP_T_32_strexb,
/*   610 */     OP_T_32_strexh,
/*   611 */     OP_T_32_strexd,
/*   612 */     OP_T_32_tbb,
/*   613 */     OP_T_32_tbh,
/*   614 */     OP_T_32_ldrexb,
/*   615 */     OP_T_32_ldrexh,
/*   616 */     OP_T_32_ldrexd,
/*   617 */     OP_T_32_ldr_imm,
/*   618 */     OP_T_32_ldrt,
/*   619 */     OP_T_32_ldr_reg,
/*   620 */     OP_T_32_ldr_lit,
/*   621 */     OP_T_32_ldrh_lit,
/*   622 */     OP_T_32_ldrh_imm,
/*   623 */     OP_T_32_ldrht,
/*   624 */     OP_T_32_ldrh_reg,
/*   625 */     OP_T_32_ldrsh_imm,
/*   626 */     OP_T_32_ldrsht,
/*   627 */     OP_T_32_ldrsh_reg,
/*   628 */     OP_T_32_ldrb_lit,
/*   629 */     OP_T_32_ldrb_imm,
/*   630 */     OP_T_32_ldrbt,
/*   631 */     OP_T_32_ldrb_reg,
/*   632 */     OP_T_32_ldrsb_lit,
/*   633 */     OP_T_32_ldrsb_imm,
/*   634 */     OP_T_32_ldrsbt,
/*   635 */     OP_T_32_ldrsb,
/*   636 */     OP_T_32_pld_imm,
/*   637 */     OP_T_32_pld_lit,
/*   638 */     OP_T_32_pld_reg,
/*   639 */     OP_T_32_pli_imm,
/*   640 */     OP_T_32_pli_lit,
/*   641 */     OP_T_32_pli_reg,
/*   642 */     OP_T_32_strb_imm,
/*   643 */     OP_T_32_strbt,
/*   644 */     OP_T_32_strb_reg,
/*   645 */     OP_T_32_strh_imm,
/*   646 */     OP_T_32_strht,
/*   647 */     OP_T_32_strh_reg,
/*   648 */     OP_T_32_str_imm,
/*   649 */     OP_T_32_strt,
/*   650 */     OP_T_32_str_reg,
/*   651 */     OP_T_32_and_reg,
/*   652 */     OP_T_32_tst_reg,
/*   653 */     OP_T_32_bic_reg,
/*   654 */     OP_T_32_orr_reg,
/*   655 */     OP_T_32_mov_reg,
/*   656 */     OP_T_32_orn_reg,
/*   657 */     OP_T_32_mvn_reg,
/*   658 */     OP_T_32_eor_reg,
/*   659 */     OP_T_32_teq_reg,
/*   660 */     OP_T_32_pkh,
/*   661 */     OP_T_32_add_reg,
/*   662 */     OP_T_32_cmn_reg,
/*   663 */     OP_T_32_adc_reg,
/*   664 */     OP_T_32_sbc_reg,
/*   665 */     OP_T_32_sub_reg,
/*   666 */     OP_T_32_cmp_reg,
/*   667 */     OP_T_32_rsb_reg,
/*   668 */     OP_T_32_lsl_reg,
/*   669 */     OP_T_32_lsr_reg,
/*   670 */     OP_T_32_asr_reg,
/*   671 */     OP_T_32_ror_reg,
/*   672 */     OP_T_32_sxtah,
/*   673 */     OP_T_32_sxth,
/*   674 */     OP_T_32_uxtah,
/*   675 */     OP_T_32_uxth,
/*   676 */     OP_T_32_sxtab16,
/*   677 */     OP_T_32_sxtb16,
/*   678 */     OP_T_32_uxtab16,
/*   679 */     OP_T_32_uxtb16,
/*   680 */     OP_T_32_sxtab,
/*   681 */     OP_T_32_sxtb,
/*   682 */     OP_T_32_uxtab,
/*   683 */     OP_T_32_uxtb,
/*   684 */     OP_T_32_sadd16,
/*   685 */     OP_T_32_sasx,
/*   686 */     OP_T_32_ssax,
/*   687 */     OP_T_32_ssub16,
/*   688 */     OP_T_32_sadd8,
/*   689 */     OP_T_32_ssub8,
/*   690 */     OP_T_32_qadd16,
/*   691 */     OP_T_32_qasx,
/*   692 */     OP_T_32_qsax,
/*   693 */     OP_T_32_qsub16,
/*   694 */     OP_T_32_qadd8,
/*   695 */     OP_T_32_qsub8,
/*   696 */     OP_T_32_shadd16,
/*   697 */     OP_T_32_shasx,
/*   698 */     OP_T_32_shsax,
/*   699 */     OP_T_32_shsub16,
/*   700 */     OP_T_32_shadd8,
/*   701 */     OP_T_32_shsub8,
/*   702 */     OP_T_32_uadd16,
/*   703 */     OP_T_32_uasx,
/*   704 */     OP_T_32_usax,
/*   705 */     OP_T_32_usub16,
/*   706 */     OP_T_32_uadd8,
/*   707 */     OP_T_32_usub8,
/*   708 */     OP_T_32_uqadd16,
/*   709 */     OP_T_32_uqasx,
/*   710 */     OP_T_32_uqsax,
/*   711 */     OP_T_32_uqsub16,
/*   712 */     OP_T_32_uqadd8,
/*   713 */     OP_T_32_uqsub8,
/*   714 */     OP_T_32_uhadd16,
/*   715 */     OP_T_32_uhasx,
/*   716 */     OP_T_32_uhsax,
/*   717 */     OP_T_32_uhsub16,
/*   718 */     OP_T_32_uhadd8,
/*   719 */     OP_T_32_uhsub8,
/*   720 */     OP_T_32_qadd,
/*   721 */     OP_T_32_qdadd,
/*   722 */     OP_T_32_qsub,
/*   723 */     OP_T_32_qdsub,
/*   724 */     OP_T_32_rev,
/*   725 */     OP_T_32_rev16,
/*   726 */     OP_T_32_rbit,
/*   727 */     OP_T_32_revsh,
/*   728 */     OP_T_32_sel,
/*   729 */     OP_T_32_clz,
/*   730 */     OP_T_32_mla,
/*   731 */     OP_T_32_mul,
/*   732 */     OP_T_32_mls,
/*   733 */     OP_T_32_smlabb,
/*   734 */     OP_T_32_smlabt,
/*   735 */     OP_T_32_smlatb,
/*   736 */     OP_T_32_smlatt,
/*   737 */     OP_T_32_smulbb,
/*   738 */     OP_T_32_smulbt,
/*   739 */     OP_T_32_smultb,
/*   740 */     OP_T_32_smultt,
/*   741 */     OP_T_32_smlad,
/*   742 */     OP_T_32_smuad,
/*   743 */     OP_T_32_smlawb,
/*   744 */     OP_T_32_smlawt,
/*   745 */     OP_T_32_smulwb,
/*   746 */     OP_T_32_smulwt,
/*   747 */     OP_T_32_smlsd,
/*   748 */     OP_T_32_smusd,
/*   749 */     OP_T_32_smmla,
/*   750 */     OP_T_32_smmul,
/*   751 */     OP_T_32_smmls,
/*   752 */     OP_T_32_usad8,
/*   753 */     OP_T_32_usada8,
/*   754 */     OP_T_32_smull,
/*   755 */     OP_T_32_sdiv,
/*   756 */     OP_T_32_umull,
/*   757 */     OP_T_32_udiv,
/*   758 */     OP_T_32_smlal,
/*   759 */     OP_T_32_smlalbb,
/*   760 */     OP_T_32_smlalbt,
/*   761 */     OP_T_32_smlaltb,
/*   762 */     OP_T_32_smlaltt,
/*   763 */     OP_T_32_smlald,
/*   764 */     OP_T_32_smlsld,
/*   765 */     OP_T_32_umlal,
/*   766 */     OP_T_32_umaal,
/*   767 */     OP_T_32_stc,
/*   768 */     OP_T_32_stc2,
/*   769 */     OP_T_32_ldc_imm,
/*   770 */     OP_T_32_ldc_lit,
/*   771 */     OP_T_32_ldc2_imm,
/*   772 */     OP_T_32_ldc2_lit,
/*   773 */     OP_T_32_mcrr,
/*   774 */     OP_T_32_mcrr2,
/*   775 */     OP_T_32_mrrc,
/*   776 */     OP_T_32_mrrc2,
/*   777 */     OP_T_32_cdp,
/*   778 */     OP_T_32_cdp2,
/*   779 */     OP_T_32_mcr,
/*   780 */     OP_T_32_mcr2,
/*   781 */     OP_T_32_mrc,
/*   782 */     OP_T_32_mrc2,


//TODO add the Adv SIMD/VFP instructions for Thumb

    OP_AFTER_LAST,
    OP_FIRST = OP_adc_imm,            /**< First real opcode. */
    OP_LAST  = OP_AFTER_LAST - 1, /**< Last real opcode. */
};


typedef byte opnd_size_t;

struct _opnd_t {
    byte kind;
    opnd_size_t size;
};

typedef struct _dr_instr_label_data_t {
    unsigned int data[4]; /**< Generic fields for storing user-controlled data */
} dr_instr_label_data_t;

struct _instr_t {
    /* flags contains the constants defined above */
    uint    flags;

    /* raw bits of length length are pointed to by the bytes field */
    byte    *bytes;
    uint    length;

    /* translation target for this instr */
    app_pc  translation;

    byte    cond;
    byte    instr_type;
    byte    opcode;

    /* we dynamically allocate dst and src arrays b/c x86 instrs can have
     * up to 8 of each of them, but most have <=2 dsts and <=3 srcs, and we
     * use this struct for un-decoded instrs too
     */
    byte    num_dsts;
    byte    num_srcs;

    union {
        struct {
            /* for efficiency everyone has a 1st src opnd, since we often just
             * decode jumps, which all have a single source (==target)
             * yes this is an extra 10 bytes, but the whole struct is still < 64 bytes!
             */
            opnd_t    src0;
            opnd_t    *srcs; /* this array has 2nd src and beyond */
            opnd_t    *dsts;
        };
        dr_instr_label_data_t label_data;
    };

    /* SJF Flags 2 contains flags or possible op2 depening on instruction type */
    uint    flags2;   /* contains flags contained in bits[7,4] of the instr
                         May contain opcode for coprocessor instrs */
    uint    cpsr;     /* CPSR flags */
    uint 	apsr; 		/*APSR flags*/

    /* this field is for the use of passes as an annotation.
     * it is also used to hold the offset of an instruction when encoding
     * pc-relative instructions.
     */
    void *note;

    /* fields for building instructions into instruction lists */
    instr_t   *prev;
    instr_t   *next;

    /*SJF Need the flags to be set in here as well
          so they can be corectly encoded out to the fcache */
    bool p_flag; // Post indexed?
    bool u_flag; // plus/minus offset?
    bool s_flag; // set cpsr flags?
    bool w_flag; // write back?
    bool l_flag; //load/store
    bool b_flag; //word or byte?
    bool d_flag; //???
    bool h_flag; //???
    bool m_flag; //For signed multiplies
    bool r_flag; //For stm to flag to overwrite cpsr with spsr

    int  shift_type;

}; /* instr_t */

byte *
instr_get_raw_bits(instr_t *instr);

void
instr_set_opcode(instr_t *instr, int opcode);

int
instr_get_opcode(instr_t *instr);

void
instr_set_apsr_valid(instr_t * instr, bool valid);

void
instr_set_operands_valid(instr_t *instr, bool valid);

void
instr_set_raw_bits(instr_t *instr, byte *addr, uint length);

#endif /* INSTRUCTION_H_ */
