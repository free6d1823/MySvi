/*
 * =====================================================================================
 *
 *       Filename:  cpuchar.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Friday, November 02, 2018 04:17:32 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  dusc (),
 *
 * =====================================================================================
 */
#ifndef CPUCHAR_H
#define CPUCHAR_H

int do_apc_trim(int argc, char* argv[]);
int do_trim_read(int argc, char* argv[]);
int do_odcm_rsense(int argc, char* argv[]);
int do_odcm_read_imeas(int argc, char* argv[]);
int do_routing(int argc, char* argv[]);
int routing_man(int argc, char* argv[]);

#endif // CPUCHAR_H
