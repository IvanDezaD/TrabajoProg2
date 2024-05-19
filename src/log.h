/*
*  Ivan Deza: 837603
*  David Hudrea: 868573
*/ 
#pragma once

#ifdef __DEBUG__
#define info(msg, ...) printf("[#] "  msg  " \n", ##__VA_ARGS__);
#define okay(msg, ...) printf("[+] "  msg  " \n", ##__VA_ARGS__);
#define myError(msg, ...) printf("[-] "  msg  " \n", ##__VA_ARGS__); printf("[-] Saliendo!");exit(EXIT_FAILURE)
#else
#define info(msg, ...)
#define okay(msg, ...)
#define myError(msg, ...) printf("[-] "  msg  " \n", ##__VA_ARGS__); printf("\033[?25h");exit(EXIT_FAILURE) 
#endif // __DEBUG__

