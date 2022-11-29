rsmelo_iqbrilhante/makefile                                                                         000664  001750  001750  00000002501 12361227142 017263  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         
RM := rm -rf

# All of the sources participating in the build are defined here
#sources
O_SRCS := 
C_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
OBJS := 
C_DEPS := 
EXECUTABLES := 

# Every subdirectory with source files must be described here
SUBDIRS := .

#Subdir
# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += ./main.c ./op_vetor.c ./operacoes_rb.c ./rb.c 

OBJS += obj/main.o obj/op_vetor.o obj/operacoes_rb.o obj/rb.o 

C_DEPS += obj/main.d obj/op_vetor.d obj/operacoes_rb.d obj/rb.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	gcc -I"include" -include"include/libtree.h" -include"include/op_vetor.h" -include"include/operacoes_rb.h" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo ' '

#Objects
USER_OBJS :=
LIBS :=

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: trab

# Tool invocations
trab: $(OBJS) $(USER_OBJS)
	@echo 'Invocando: GCC C Linker'
	gcc  -o "trab" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finalizando: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) trab
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
                                                                                                                                                                                               rsmelo_iqbrilhante/include/libtree.h                                                                000664  001750  001750  00000015607 12052425212 021013  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         /*
 * libtree.h - this file is part of Libtree.
 *
 * Copyright (C) 2010 Franck Bui-Huu <fbuihuu@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */
#ifndef _LIBTREE_H
#define _LIBTREE_H

#include <stdint.h>
#include <stddef.h>

/*
 * The definition has been stolen from the Linux kernel.
 */
#ifdef __GNUC__
#  define bstree_container_of(node, type, member) ({			\
	const struct bstree_node *__mptr = (node);			\
	(type *)( (char *)__mptr - offsetof(type,member) );})
#  define rbtree_container_of(node, type, member) ({			\
	const struct rbtree_node *__mptr = (node);			\
	(type *)( (char *)__mptr - offsetof(type,member) );})
#  define avltree_container_of(node, type, member) ({			\
	const struct avltree_node *__mptr = (node);			\
	(type *)( (char *)__mptr - offsetof(type,member) );})
#  define splaytree_container_of(node, type, member) ({			\
	const struct splaytree_node *__mptr = (node);			\
	(type *)( (char *)__mptr - offsetof(type,member) );})
#else
#  define bstree_container_of(node, type, member)			\
	((type *)((char *)(node) - offsetof(type, member)))
#  define rbtree_container_of(node, type, member)			\
	((type *)((char *)(node) - offsetof(type, member)))
#  define avltree_container_of(node, type, member)			\
	((type *)((char *)(node) - offsetof(type, member)))
#  define splaytree_container_of(node, type, member)			\
	((type *)((char *)(node) - offsetof(type, member)))
#endif	/* __GNUC__ */

/*
 * Threaded binary search tree
 */
#ifdef UINTPTR_MAX

struct bstree_node {
	uintptr_t left, right;
} __attribute__((aligned(2)));

#else

struct bstree_node {
	struct bstree_node *left, *right;
	unsigned left_is_thread:1;
	unsigned right_is_thread:1;
};

#endif	/* UINTPTR_MAX */

typedef int (*bstree_cmp_fn_t)(const struct bstree_node *, const struct bstree_node *);

struct bstree {
	struct bstree_node *root;
	bstree_cmp_fn_t cmp_fn;
	struct bstree_node *first, *last;
	uint64_t reserved[4];
};

struct bstree_node *bstree_first(const struct bstree *tree);
struct bstree_node *bstree_last(const struct bstree *tree);
struct bstree_node *bstree_next(const struct bstree_node *node);
struct bstree_node *bstree_prev(const struct bstree_node *node);

struct bstree_node *bstree_lookup(const struct bstree_node *key, const struct bstree *tree);
struct bstree_node *bstree_insert(struct bstree_node *node, struct bstree *tree);
void bstree_remove(struct bstree_node *node, struct bstree *tree);
void bstree_replace(struct bstree_node *old, struct bstree_node *node, struct bstree *tree);
int bstree_init(struct bstree *tree, bstree_cmp_fn_t cmp, unsigned long flags);

/*
 * Red-black tree
 */
enum rb_color {
	RB_BLACK,
	RB_RED,
};

#ifdef UINTPTR_MAX

struct rbtree_node {
	struct rbtree_node *left, *right;
	uintptr_t parent;
} __attribute__((aligned(2)));

#else

struct rbtree_node {
	struct rbtree_node *left, *right;
	struct rbtree_node *parent;
	enum rb_color color;
};

#endif	/* UINTPTR_MAX */

typedef int (*rbtree_cmp_fn_t)(const struct rbtree_node *, const struct rbtree_node *);

struct rbtree {
	struct rbtree_node *root;
	rbtree_cmp_fn_t cmp_fn;
	struct rbtree_node *first, *last;
	uint64_t reserved[4];
};

struct rbtree_node *rbtree_first(const struct rbtree *tree);
struct rbtree_node *rbtree_last(const struct rbtree *tree);
struct rbtree_node *rbtree_next(const struct rbtree_node *node);
struct rbtree_node *rbtree_prev(const struct rbtree_node *node);

struct rbtree_node *rbtree_lookup(const struct rbtree_node *key, const struct rbtree *tree);
struct rbtree_node *rbtree_insert(struct rbtree_node *node, struct rbtree *tree);
void rbtree_remove(struct rbtree_node *node, struct rbtree *tree);
void rbtree_replace(struct rbtree_node *old, struct rbtree_node *node, struct rbtree *tree);
int rbtree_init(struct rbtree *tree, rbtree_cmp_fn_t cmp, unsigned long flags);

/*
 * AVL tree
 */
#if defined UINTPTR_MAX && UINTPTR_MAX == UINT64_MAX

struct avltree_node {
	struct avltree_node *left, *right;
	uintptr_t parent;		/* balance factor [0:4] */
} __attribute__((aligned(8)));

#else

struct avltree_node {
	struct avltree_node *left, *right;
	struct avltree_node *parent;
	signed balance:3;		/* balance factor [-2:+2] */
};

#endif

typedef int (*avltree_cmp_fn_t)(const struct avltree_node *, const struct avltree_node *);

struct avltree {
	struct avltree_node *root;
	avltree_cmp_fn_t cmp_fn;
	int height;
	struct avltree_node *first, *last;
	uint64_t reserved[4];
};

struct avltree_node *avltree_first(const struct avltree *tree);
struct avltree_node *avltree_last(const struct avltree *tree);
struct avltree_node *avltree_next(const struct avltree_node *node);
struct avltree_node *avltree_prev(const struct avltree_node *node);

struct avltree_node *avltree_lookup(const struct avltree_node *key, const struct avltree *tree);
struct avltree_node *avltree_insert(struct avltree_node *node, struct avltree *tree);
void avltree_remove(struct avltree_node *node, struct avltree *tree);
void avltree_replace(struct avltree_node *old, struct avltree_node *node, struct avltree *tree);
int avltree_init(struct avltree *tree, avltree_cmp_fn_t cmp, unsigned long flags);

/*
 * Splay tree
 */
#ifdef UINTPTR_MAX

struct splaytree_node {
	uintptr_t left, right;
} __attribute__((aligned(2)));

#else

struct splaytree_node {
	struct splaytree_node *left, *right;
	unsigned left_is_thread:1;
	unsigned right_is_thread:1;
};

#endif

typedef int (*splaytree_cmp_fn_t)(const struct splaytree_node *, const struct splaytree_node *);

struct splaytree {
	struct splaytree_node *root;
	struct splaytree_node *first, *last;
	splaytree_cmp_fn_t cmp_fn;
	uint64_t reserved[4];
};

struct splaytree_node *splaytree_first(const struct splaytree *tree);
struct splaytree_node *splaytree_last(const struct splaytree *tree);
struct splaytree_node *splaytree_next(const struct splaytree_node *node);
struct splaytree_node *splaytree_prev(const struct splaytree_node *node);

struct splaytree_node *splaytree_lookup(const struct splaytree_node *key, struct splaytree *tree);
struct splaytree_node *splaytree_insert( struct splaytree_node *node, struct splaytree *tree);
void splaytree_remove(struct splaytree_node *node, struct splaytree *tree);
void splaytree_replace(struct splaytree_node *old, struct splaytree_node *node, struct splaytree *tree);
int splaytree_init(struct splaytree *tree, splaytree_cmp_fn_t cmp, unsigned long flags);

#endif /* _LIBTREE_H */
                                                                                                                         rsmelo_iqbrilhante/Leiame.txt                                                                       000664  001750  001750  00000002544 12361556373 017542  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         Identificação:
	Renato Silva de Melo
	login: rsmelo
	Ítalo Quirino Brilhante
	login: iqbrilhante
	
Observações:
	O código fonte está dividido em arquivos e diretórios.
	No diretório raiz estão os fontes .c e o makefile, para compilação é preciso executar apenas o camando 'make' no diretório raiz.
	No diretório obj/ estão os arquivos .o gerados na compilação.
	No diretório include/ encontram-se os cabeçalhos .h do trabalho, são eles: op_vetor.h, operacoes_rb.h, e libtree.h
		libtree.h é uma biblioteca opensource que implementa estruturas de dados em árvores, contém a implementação das árvores BST, AVL, RedBlack e Splay. O trabalho foi testado com todas elas, obtendo aproximadamente o mesmo desempenho para todas. Mas optou-se por utilizar árvore red black (arquivo rb.c).
	O programa utiliza a árvore como estrutura pra armazenar a coleção de conjuntos, e armazena os elementos dos conjuntos em vetores.
	op_vetor.c: implementa operações que são feitas em vetor, tais como, comparação, busca binária, exibição e etc.
	operacoes_rb.c: implementa as operações de inserção, remoção, consulta e exibição dos conjuntos na árvore.
	main.c: faz leitura das entradas e a chamada para as devidas operações em conjuntos.
	
Caso não seja permitido o uso da biblioteca libtree.h, temos a versão com a árvore implementada por nós.
                                                                                                                                                            rsmelo_iqbrilhante/include/op_vetor.h                                                               000664  001750  001750  00000000716 12361234777 021236  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         /*
 * op_vetor.h
 *
 *  Created on: 08/07/2014
 *      Author: renato, italo
 */

#ifndef OP_VETOR_H_
#define OP_VETOR_H_

/*
Arquivo de cabeçalho para as operações que serão realizadas em
 vetores, uma interface para op_vetor.c
*/

int buscaBinaria( int k, int n, int *v);

int pesquisaBin( int k, int n, int v[], int j);

void imprimeVetor(int vet[], int n);

int contemSubConj(int* conj,int tamConj,int* subConj,int tamSubConj);

#endif /* OP_VETOR_H_ */
                                                  rsmelo_iqbrilhante/.project                                                                         000664  001750  001750  00000001364 12357000552 017237  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         <?xml version="1.0" encoding="UTF-8"?>
<projectDescription>
	<name>trab</name>
	<comment></comment>
	<projects>
	</projects>
	<buildSpec>
		<buildCommand>
			<name>org.eclipse.cdt.managedbuilder.core.genmakebuilder</name>
			<triggers>clean,full,incremental,</triggers>
			<arguments>
			</arguments>
		</buildCommand>
		<buildCommand>
			<name>org.eclipse.cdt.managedbuilder.core.ScannerConfigBuilder</name>
			<triggers>full,incremental,</triggers>
			<arguments>
			</arguments>
		</buildCommand>
	</buildSpec>
	<natures>
		<nature>org.eclipse.cdt.core.cnature</nature>
		<nature>org.eclipse.cdt.managedbuilder.core.managedBuildNature</nature>
		<nature>org.eclipse.cdt.managedbuilder.core.ScannerConfigNature</nature>
	</natures>
</projectDescription>
                                                                                                                                                                                                                                                                            rsmelo_iqbrilhante/.cproject                                                                        000664  001750  001750  00000031705 12360031673 017406  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         <?xml version="1.0" encoding="UTF-8" standalone="no"?>
<?fileVersion 4.0.0?><cproject storage_type_id="org.eclipse.cdt.core.XmlProjectDescriptionStorage">
	<storageModule moduleId="org.eclipse.cdt.core.settings">
		<cconfiguration id="cdt.managedbuild.config.gnu.exe.debug.1419078047">
			<storageModule buildSystemId="org.eclipse.cdt.managedbuilder.core.configurationDataProvider" id="cdt.managedbuild.config.gnu.exe.debug.1419078047" moduleId="org.eclipse.cdt.core.settings" name="Debug">
				<externalSettings/>
				<extensions>
					<extension id="org.eclipse.cdt.core.GmakeErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.CWDLocator" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GCCErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GASErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GLDErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.ELF" point="org.eclipse.cdt.core.BinaryParser"/>
				</extensions>
			</storageModule>
			<storageModule moduleId="cdtBuildSystem" version="4.0.0">
				<configuration artifactName="${ProjName}" buildArtefactType="org.eclipse.cdt.build.core.buildArtefactType.exe" buildProperties="org.eclipse.cdt.build.core.buildType=org.eclipse.cdt.build.core.buildType.debug,org.eclipse.cdt.build.core.buildArtefactType=org.eclipse.cdt.build.core.buildArtefactType.exe" cleanCommand="rm -rf" description="" id="cdt.managedbuild.config.gnu.exe.debug.1419078047" name="Debug" parent="cdt.managedbuild.config.gnu.exe.debug">
					<folderInfo id="cdt.managedbuild.config.gnu.exe.debug.1419078047." name="/" resourcePath="">
						<toolChain id="cdt.managedbuild.toolchain.gnu.exe.debug.1650121699" name="Linux GCC" superClass="cdt.managedbuild.toolchain.gnu.exe.debug">
							<targetPlatform id="cdt.managedbuild.target.gnu.platform.exe.debug.1849118638" name="Debug Platform" superClass="cdt.managedbuild.target.gnu.platform.exe.debug"/>
							<builder buildPath="${workspace_loc:/trab}/Debug" id="cdt.managedbuild.target.gnu.builder.exe.debug.1470588022" keepEnvironmentInBuildfile="false" managedBuildOn="true" name="Gnu Make Builder" superClass="cdt.managedbuild.target.gnu.builder.exe.debug"/>
							<tool id="cdt.managedbuild.tool.gnu.archiver.base.89551775" name="GCC Archiver" superClass="cdt.managedbuild.tool.gnu.archiver.base"/>
							<tool id="cdt.managedbuild.tool.gnu.cpp.compiler.exe.debug.1263133778" name="GCC C++ Compiler" superClass="cdt.managedbuild.tool.gnu.cpp.compiler.exe.debug">
								<option id="gnu.cpp.compiler.exe.debug.option.optimization.level.1335790588" name="Optimization Level" superClass="gnu.cpp.compiler.exe.debug.option.optimization.level" value="gnu.cpp.compiler.optimization.level.none" valueType="enumerated"/>
								<option id="gnu.cpp.compiler.exe.debug.option.debugging.level.707783834" name="Debug Level" superClass="gnu.cpp.compiler.exe.debug.option.debugging.level" value="gnu.cpp.compiler.debugging.level.max" valueType="enumerated"/>
							</tool>
							<tool command="gcc" id="cdt.managedbuild.tool.gnu.c.compiler.exe.debug.1368385430" name="GCC C Compiler" superClass="cdt.managedbuild.tool.gnu.c.compiler.exe.debug">
								<option defaultValue="gnu.c.optimization.level.none" id="gnu.c.compiler.exe.debug.option.optimization.level.1038538825" name="Optimization Level" superClass="gnu.c.compiler.exe.debug.option.optimization.level" value="gnu.c.optimization.level.most" valueType="enumerated"/>
								<option id="gnu.c.compiler.exe.debug.option.debugging.level.1571582119" name="Debug Level" superClass="gnu.c.compiler.exe.debug.option.debugging.level" value="gnu.c.debugging.level.max" valueType="enumerated"/>
								<option id="gnu.c.compiler.option.dialect.std.1375038020" name="Language standard" superClass="gnu.c.compiler.option.dialect.std" value="gnu.c.compiler.dialect.default" valueType="enumerated"/>
								<option id="gnu.c.compiler.option.optimization.flags.1786713522" name="Other optimization flags" superClass="gnu.c.compiler.option.optimization.flags" value="" valueType="string"/>
								<option id="gnu.c.compiler.option.include.paths.527315325" superClass="gnu.c.compiler.option.include.paths" valueType="includePath">
									<listOptionValue builtIn="false" value="&quot;${workspace_loc:/${ProjName}/include}&quot;"/>
								</option>
								<option id="gnu.c.compiler.option.include.files.1909052539" superClass="gnu.c.compiler.option.include.files" valueType="includeFiles">
									<listOptionValue builtIn="false" value="&quot;${workspace_loc:/${ProjName}/include/libtree.h}&quot;"/>
									<listOptionValue builtIn="false" value="&quot;${workspace_loc:/${ProjName}/include/op_vetor.h}&quot;"/>
									<listOptionValue builtIn="false" value="&quot;${workspace_loc:/${ProjName}/include/operacoes_rb.h}&quot;"/>
								</option>
								<inputType id="cdt.managedbuild.tool.gnu.c.compiler.input.953237985" superClass="cdt.managedbuild.tool.gnu.c.compiler.input"/>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.c.linker.exe.debug.981240394" name="GCC C Linker" superClass="cdt.managedbuild.tool.gnu.c.linker.exe.debug">
								<inputType id="cdt.managedbuild.tool.gnu.c.linker.input.484919932" superClass="cdt.managedbuild.tool.gnu.c.linker.input">
									<additionalInput kind="additionalinputdependency" paths="$(USER_OBJS)"/>
									<additionalInput kind="additionalinput" paths="$(LIBS)"/>
								</inputType>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.cpp.linker.exe.debug.1725999208" name="GCC C++ Linker" superClass="cdt.managedbuild.tool.gnu.cpp.linker.exe.debug"/>
							<tool id="cdt.managedbuild.tool.gnu.assembler.exe.debug.358733328" name="GCC Assembler" superClass="cdt.managedbuild.tool.gnu.assembler.exe.debug">
								<inputType id="cdt.managedbuild.tool.gnu.assembler.input.1979342594" superClass="cdt.managedbuild.tool.gnu.assembler.input"/>
							</tool>
						</toolChain>
					</folderInfo>
					<sourceEntries>
						<entry excluding="include" flags="VALUE_WORKSPACE_PATH|RESOLVED" kind="sourcePath" name=""/>
						<entry flags="VALUE_WORKSPACE_PATH|RESOLVED" kind="sourcePath" name="include"/>
					</sourceEntries>
				</configuration>
			</storageModule>
			<storageModule moduleId="org.eclipse.cdt.core.externalSettings"/>
		</cconfiguration>
		<cconfiguration id="cdt.managedbuild.config.gnu.exe.release.954904282">
			<storageModule buildSystemId="org.eclipse.cdt.managedbuilder.core.configurationDataProvider" id="cdt.managedbuild.config.gnu.exe.release.954904282" moduleId="org.eclipse.cdt.core.settings" name="Release">
				<externalSettings/>
				<extensions>
					<extension id="org.eclipse.cdt.core.GmakeErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.CWDLocator" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GCCErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GASErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.GLDErrorParser" point="org.eclipse.cdt.core.ErrorParser"/>
					<extension id="org.eclipse.cdt.core.ELF" point="org.eclipse.cdt.core.BinaryParser"/>
				</extensions>
			</storageModule>
			<storageModule moduleId="cdtBuildSystem" version="4.0.0">
				<configuration artifactName="${ProjName}" buildArtefactType="org.eclipse.cdt.build.core.buildArtefactType.exe" buildProperties="org.eclipse.cdt.build.core.buildType=org.eclipse.cdt.build.core.buildType.release,org.eclipse.cdt.build.core.buildArtefactType=org.eclipse.cdt.build.core.buildArtefactType.exe" cleanCommand="rm -rf" description="" id="cdt.managedbuild.config.gnu.exe.release.954904282" name="Release" parent="cdt.managedbuild.config.gnu.exe.release">
					<folderInfo id="cdt.managedbuild.config.gnu.exe.release.954904282." name="/" resourcePath="">
						<toolChain id="cdt.managedbuild.toolchain.gnu.exe.release.338622109" name="Linux GCC" superClass="cdt.managedbuild.toolchain.gnu.exe.release">
							<targetPlatform id="cdt.managedbuild.target.gnu.platform.exe.release.750185326" name="Debug Platform" superClass="cdt.managedbuild.target.gnu.platform.exe.release"/>
							<builder buildPath="${workspace_loc:/trab}/Release" id="cdt.managedbuild.target.gnu.builder.exe.release.2018796327" keepEnvironmentInBuildfile="false" managedBuildOn="true" name="Gnu Make Builder" superClass="cdt.managedbuild.target.gnu.builder.exe.release"/>
							<tool id="cdt.managedbuild.tool.gnu.archiver.base.786950045" name="GCC Archiver" superClass="cdt.managedbuild.tool.gnu.archiver.base"/>
							<tool id="cdt.managedbuild.tool.gnu.cpp.compiler.exe.release.750547368" name="GCC C++ Compiler" superClass="cdt.managedbuild.tool.gnu.cpp.compiler.exe.release">
								<option id="gnu.cpp.compiler.exe.release.option.optimization.level.1673969734" name="Optimization Level" superClass="gnu.cpp.compiler.exe.release.option.optimization.level" value="gnu.cpp.compiler.optimization.level.most" valueType="enumerated"/>
								<option id="gnu.cpp.compiler.exe.release.option.debugging.level.86475301" name="Debug Level" superClass="gnu.cpp.compiler.exe.release.option.debugging.level" value="gnu.cpp.compiler.debugging.level.none" valueType="enumerated"/>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.c.compiler.exe.release.1152991982" name="GCC C Compiler" superClass="cdt.managedbuild.tool.gnu.c.compiler.exe.release">
								<option defaultValue="gnu.c.optimization.level.most" id="gnu.c.compiler.exe.release.option.optimization.level.2079761875" name="Optimization Level" superClass="gnu.c.compiler.exe.release.option.optimization.level" valueType="enumerated"/>
								<option id="gnu.c.compiler.exe.release.option.debugging.level.537080838" name="Debug Level" superClass="gnu.c.compiler.exe.release.option.debugging.level" value="gnu.c.debugging.level.none" valueType="enumerated"/>
								<inputType id="cdt.managedbuild.tool.gnu.c.compiler.input.1578681127" superClass="cdt.managedbuild.tool.gnu.c.compiler.input"/>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.c.linker.exe.release.1227698444" name="GCC C Linker" superClass="cdt.managedbuild.tool.gnu.c.linker.exe.release">
								<inputType id="cdt.managedbuild.tool.gnu.c.linker.input.702742240" superClass="cdt.managedbuild.tool.gnu.c.linker.input">
									<additionalInput kind="additionalinputdependency" paths="$(USER_OBJS)"/>
									<additionalInput kind="additionalinput" paths="$(LIBS)"/>
								</inputType>
							</tool>
							<tool id="cdt.managedbuild.tool.gnu.cpp.linker.exe.release.213508964" name="GCC C++ Linker" superClass="cdt.managedbuild.tool.gnu.cpp.linker.exe.release"/>
							<tool id="cdt.managedbuild.tool.gnu.assembler.exe.release.1138593054" name="GCC Assembler" superClass="cdt.managedbuild.tool.gnu.assembler.exe.release">
								<inputType id="cdt.managedbuild.tool.gnu.assembler.input.1808136957" superClass="cdt.managedbuild.tool.gnu.assembler.input"/>
							</tool>
						</toolChain>
					</folderInfo>
					<sourceEntries>
						<entry excluding="include" flags="VALUE_WORKSPACE_PATH|RESOLVED" kind="sourcePath" name=""/>
						<entry flags="VALUE_WORKSPACE_PATH|RESOLVED" kind="sourcePath" name="include"/>
					</sourceEntries>
				</configuration>
			</storageModule>
			<storageModule moduleId="org.eclipse.cdt.core.externalSettings"/>
		</cconfiguration>
	</storageModule>
	<storageModule moduleId="cdtBuildSystem" version="4.0.0">
		<project id="trab.cdt.managedbuild.target.gnu.exe.212638719" name="Executable" projectType="cdt.managedbuild.target.gnu.exe"/>
	</storageModule>
	<storageModule moduleId="scannerConfiguration">
		<autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
		<scannerConfigBuildInfo instanceId="cdt.managedbuild.config.gnu.exe.release.954904282;cdt.managedbuild.config.gnu.exe.release.954904282.;cdt.managedbuild.tool.gnu.c.compiler.exe.release.1152991982;cdt.managedbuild.tool.gnu.c.compiler.input.1578681127">
			<autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
		</scannerConfigBuildInfo>
		<scannerConfigBuildInfo instanceId="cdt.managedbuild.config.gnu.exe.debug.1419078047;cdt.managedbuild.config.gnu.exe.debug.1419078047.;cdt.managedbuild.tool.gnu.c.compiler.exe.debug.1368385430;cdt.managedbuild.tool.gnu.c.compiler.input.953237985">
			<autodiscovery enabled="true" problemReportingEnabled="true" selectedProfileId=""/>
		</scannerConfigBuildInfo>
	</storageModule>
	<storageModule moduleId="org.eclipse.cdt.core.LanguageSettingsProviders"/>
	<storageModule moduleId="refreshScope" versionNumber="2">
		<configuration configurationName="Release">
			<resource resourceType="PROJECT" workspacePath="/trab"/>
		</configuration>
		<configuration configurationName="Debug">
			<resource resourceType="PROJECT" workspacePath="/trab"/>
		</configuration>
	</storageModule>
	<storageModule moduleId="org.eclipse.cdt.make.core.buildtargets"/>
	<storageModule moduleId="org.eclipse.cdt.internal.ui.text.commentOwnerProjectMappings"/>
</cproject>
                                                           rsmelo_iqbrilhante/                                                                                 000775  001750  001750  00000000000 12361557061 015573  5                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         rsmelo_iqbrilhante/op_vetor.c                                                                       000664  001750  001750  00000003762 12361555457 017613  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         /*
 * op_vetor.c
 *
 *  Created on: 08/07/2014
 *      Author: Renato Melo, Ítalo Quirino
 */
#include <stdio.h>
#define true 1 // para usar como tipo booleano
#define false 0

typedef int bool; //Definição do tipo booleano

// Busca binária modificada para validação
// A função abaixo recebe um número k e um vetor
// crescente v[0..n-1]. Ela devolve verdadeiro
// se v[meio] >= k ou devolve falso se não existe
// um valor maior ou igual a k
bool buscaBinaria( int k, int n, int v[]) {
	int inicio = 0;
	int meio;
	int fim = n-1;
	while (inicio <= fim) {
		meio = (inicio + fim)/2;
		if (v[meio] > k)
			return true;
		else
			inicio = meio + 1;
   }
   return false;
}

// A função abaixo recebe um número k e um vetorf,
// crescente v[0..n-1] e um indice j marcando o inicio do vetor.
// Ela devolve o indice do elemento procurado se v[meio] == k 
// ou devolve -1 se não existe um valo igual a k
// Por ser uma busca binária seu tempo de execução é O(log n)
int pesquisaBin(int k, int n, int v[], int j) {
	int inicio = j;
	int meio;
	int fim = n-1;
	while (inicio <= fim) {
		meio = (inicio + fim)/2;
		if (k == v[meio])
			return meio;
		else if (v[meio] > k)
			fim = meio -1;
		else
			inicio = meio + 1;
   }
   return -1;
}

//Exibe os elementos um vetor de tamanho n
void imprimeVetor(int vet[], int n){
	int i;
	printf("%d",n);
	for (i = 0; i < n; i += 1)
		printf(" %d",vet[i]);
	printf("\n");
}

// Recebe um conjunto, um subconjunto e seus respectivos tamanhos
// Devolve verdadeiro se subconj está contido em conj.
// Utiliza busca binária para encontrar cada elemento de subConj contido em conj,
// seguindo a pesquisa a partir do ultimo elemento encontrado,
// garantindo assim que as buscas que seguem após a primeira, 
// executem em tempo menor que O(log n)
bool contemSubConj(int* conj,int tamConj,int* subConj,int tamSubConj){
    int i,j = 0;
    for(i = 0; i < tamSubConj; i++){
		j = pesquisaBin(subConj[i],tamConj,conj,j);
		if(j == -1){
			return false;
		}
    }
    return true;
}
              rsmelo_iqbrilhante/obj/                                                                             000775  001750  001750  00000000000 12361557112 016342  5                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         rsmelo_iqbrilhante/main.c                                                                           000664  001750  001750  00000004335 12361554675 016700  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         /*
 * main.c
 *
 *  Created on: 08/07/2014
 *      Author: Renato Melo, Ítalo Quirino
 */
#include <stdio.h>
#include <stdlib.h>
#include "operacoes_rb.h"

/*
 Utilizamos entrada e saida padrão (scanf e printf);
 Isso obedece a regra da especificação, pode ser redirecionado
 de um arquivo e para um arquivo como pede na especificação;
 */

/**
 Leitura das entradas, a primeira linha é um valor k, que é o
 maior elemento que pode existir nos conjuntos. Uma operação
 (+,-,=,*), um valor n, que será o tamanho dos conjuntos
 e os elementos do conjunto.
 */
int main(void) {
	static int *vet;

	char fimdalinha;
	char op = '1'; // Inicia com um falor qualquer
	int n = 0;
	int i, k;

	//Variavel para receber o retorno do scanf
	int unused __attribute__((unused));

	iniciar_colecao();


	unused = scanf("%d", &k); //Lê o primeiro argumento da entrada

	//Lê o enter e vai para a proxima linha
	unused = scanf("%c", &fimdalinha);

	
	while (scanf("%c", &op)) {//Lê a operação

		//Sai do laço se chegar ao fim do arquivo
		if (op == '0')
			break;

		//Se a operação não é * lê o restante dos argumentos
		//caso contrario ignora o restante da linha
		if (op != '*') {

			//Lê os elementos do conjunto e insere em um vetor
			if (scanf("%d", &n)) {
				vet = (int*) malloc(n * sizeof(int));
				for (i = 0; i < n; i++)
					unused = scanf("%d", &vet[i]);
			}
			//Lê o enter e vai para a proxima linha
			unused = scanf("%c", &fimdalinha);
		} else
			unused = scanf("%c", &fimdalinha);

		switch (op) {
		case '+':		//Operação de inserção de um conjunto
			add(n, vet);
			break;
		case '-':		//Operação de remoção de um conjunto
			del(n, vet);
			break;
		case '=':
			igualdade(n, vet);
			break;
		case '<':
			//Imprime todos os conj que são subconjuntos
			//do conj envolvido
			imprimeSubConj(n, vet);
			break;
		case '/':
			//Remove todos os conj que são subconjuntos
			//do conj envolvido
			removeSuperConj(n, vet);
			break;
		case '>':
			//Imprime todos os conj que são superconjuntos
			//do conj envolvido
			imprimeSuperConj(n, vet);
			break;
		case '*':
			//Mostra todos os subconjuntos em ordem crescente
			exibir();
			break;
		default:
			printf("Operação inválida.\n");
			break;
		}
	}
	return 0;
}
                                                                                                                                                                                                                                                                                                   rsmelo_iqbrilhante/include/operacoes_rb.h                                                           000664  001750  001750  00000000656 12357001165 022033  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         /*
 * operacoes_rb.h
 *
 *  Created on: 08/07/2014
 *      Author: renato
 */

#ifndef OPERACOES_RB_H_
#define OPERACOES_RB_H_

void iniciar_colecao(void);
//+
void add(int n, int *vet);
//-
void del(int n, int *vet);
//=
void igualdade(int n, int *vet);
//*
void exibir();
//<
void imprimeSubConj(int n, int* vet);
//>
void imprimeSuperConj(int n,int* vet);

void removeSuperConj(int n, int* vet);


#endif /* OPERACOES_RB_H_ */
                                                                                  rsmelo_iqbrilhante/include/                                                                         000775  001750  001750  00000000000 12361234777 017224  5                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         rsmelo_iqbrilhante/operacoes_rb.c                                                                   000664  001750  001750  00000012434 12361555272 020410  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         /*
 * operacoes_rb.c
 *
 *  Created on: 08/07/2014
 *      Author: Renato, Ítalo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libtree.h"
#include "op_vetor.h"

//representa os conjuntos da coleção
//além dos valores, encapsula um nó da arvore para o encademento.
typedef struct conjunto {
        int n;
        int *valores;
        struct rbtree_node node;
} Conjunto;

//Cria uma arvore rubro negra
struct rbtree tree;

//Encapsula os valores recebidos da entrada em um Conjunto
//Devolve um um *Conjunto para as operações na árvore
Conjunto *criar_conjunto(int n, int *valores)
{
	Conjunto* novo = (Conjunto*) malloc(sizeof (Conjunto));
	novo->valores = valores;
	novo->n = n;
	return novo;
}

//Função de comparação utilizada nas operações da árvore.
//Compara os conjuntos, retorna zero se for igual ou a difença do nó a com b
//Esta função permite a que os conjuntos sejam manipulados na coleção
// de acordo com a sua ordem lexicografica.
//A chave de comparação é o tamanho do conjunto, em caso de conjuntos de 
//tamanhos iguais se considera os elementos do conjunto.
int comparacao(const struct rbtree_node *a, const struct rbtree_node *b)
{
        Conjunto *p = rbtree_container_of(a, Conjunto, node);
        Conjunto *q = rbtree_container_of(b, Conjunto, node);
        int result = p->n - q->n;
        if(result == 0){
        	int i;
        	for (i = 0; i < p->n; i += 1)
        	{
        		if(p->valores[i] != q->valores[i])
        			return p->valores[i] - q->valores[i];
        	}
        	result = 0;
        }
        return result;
}


//Inicializa a arvore vazia, passando como argumento
//o endereço da arvore e a funcao de comparacao
void iniciar_colecao(void){
	rbtree_init(&tree, comparacao, 0);
}

//Insere um conjunto na coleção
// rbtree_insert() retorna NULL se o conj a ser inserido ainda não existe
// Nesse caso a inserção é realizada, caso contrario add() devolve erro.
void add(int n, int *vet){

	Conjunto *conj = criar_conjunto(n,vet);
	if(!rbtree_insert((struct rbtree_node *) &conj->node, &tree))
		printf("0\n");
	else
		printf("E\n0\n");
}
//Remove um conjunto da coleção
//Primeiro verifica-se se o conj existe para depois executar a remoção
//se não exite devolve erro.
void del(int n, int *vet){
	Conjunto *conj = criar_conjunto(n,vet);

	Conjunto *c;
	struct rbtree_node *nodo;
	nodo = rbtree_lookup ((struct rbtree_node *) &conj->node, &tree);
	if (nodo != NULL) {
		c = rbtree_container_of(nodo, Conjunto, node);
		rbtree_remove (&c->node, &tree);
		free (c);
		printf("0\n");
	}else
		printf("E\n0\n");
}

//=
//realiza uma pesquisa na coleção pelo conjunto envolvido
void igualdade(int n, int *vet){
	Conjunto *conj = criar_conjunto(n,vet);

	struct rbtree_node *result;
	result = rbtree_lookup ((struct rbtree_node *) &conj->node, &tree);
	if (result != NULL)
		printf("0\n");
	else
		printf("E\n0\n");
}

//'*'
//Mostra todos os elementos da árvore
void exibir(){
    struct rbtree_node *nodo;
    Conjunto *c;
    nodo = rbtree_first(&tree);
    while (nodo) {
        c = rbtree_container_of(nodo, Conjunto, node);
		imprimeVetor(c->valores,c->n);
        nodo = rbtree_next(nodo);
    }
    printf("0\n");
}

/* operação '<'
Esta operação deve listar todos os conjuntos da coleção que são
subconjuntos próprios do conjunto envolvido na operação
*/
//Itera pela árvore utilizando os recursos da biblioteca
// e imprime os devidos conjuntos
void imprimeSubConj(int n, int* vet){
	char saida[] = "0\n";
	struct rbtree_node *nodo;
    Conjunto *c;
    nodo = rbtree_first(&tree);
    while (nodo) {
        c = rbtree_container_of(nodo, Conjunto, node);

		if (n > c->n){

			if (contemSubConj(vet,n,c->valores,c->n)){
				imprimeVetor(c->valores,c->n);
				strcpy(saida, "0\n");
			}
		}

        nodo = rbtree_next(nodo);
    }
    printf("%s",saida);
}

// operação '>'
/*
Esta operação deve listar todos os conjuntos da coleção que são
superconjuntos próprios do conjunto envolvido na operação.
*/
//Itera pela árvore utilizando os recursos da biblioteca
// e imprime os devidos conjuntos
void imprimeSuperConj(int n, int* vet){
	char saida[] = "0\n";
	struct rbtree_node *nodo;
    Conjunto *c;
    nodo = rbtree_first(&tree);
    while (nodo) {
        c = rbtree_container_of(nodo, Conjunto, node);
		if (n < c->n){
			if (contemSubConj(c->valores,c->n,vet,n)){
				imprimeVetor(c->valores,c->n);
				strcpy(saida, "0\n");
			}
		}
        nodo = rbtree_next(nodo);
    }
    printf("%s",saida);
}

// operação '/'
/*Esta operação remove da coleção todos os conjuntos que
são superconjuntos próprios do conjunto envolvido na operação. */
//Função iterativa que atravessa a árvore em ordem, realiza a comparação
// e a devida remoção para cada conjunto visitado.
void removeSuperConj(int n, int* vet){
	Conjunto *c;
	struct rbtree_node *atual, *pilha[1000];
	int topo = 0;
	char saida[] = "E\n0\n";
	atual = tree.root;
	while(atual != NULL || topo > 0){		
		if (atual != NULL){
			pilha[topo++] = atual;

			atual = atual->left;
		}else{			
			atual = pilha[--topo];
			
			c = rbtree_container_of(atual, Conjunto, node);
			if (n > c->n){
				if (contemSubConj(c->valores,c->n,vet,n)){
					rbtree_remove (atual, &tree);
					free (c);
					strcpy(saida, "0\n");
				}
			}
			
			atual = atual->right;
		}
	}
	printf("%s",saida);
}
                                                                                                                                                                                                                                    rsmelo_iqbrilhante/rb.c                                                                             000664  001750  001750  00000025014 12052425212 016331  0                                                                                                    ustar 00renato                          renato                          000000  000000                                                                                                                                                                         /*
 * rbtree - Implements a red-black tree with parent pointers.
 *
 * Copyright (C) 2010 Franck Bui-Huu <fbuihuu@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

/*
 * For recall a red-black tree has the following properties:
 *
 *     1. All nodes are either BLACK or RED
 *     2. Leafs are BLACK
 *     3. A RED node has BLACK children only
 *     4. Path from a node to any leafs has the same number of BLACK nodes.
 *
 */
#include "libtree.h"

/*
 * Some helpers
 */
#ifdef UINTPTR_MAX

static inline enum rb_color get_color(const struct rbtree_node *node)
{
	return node->parent & 1;
}

static inline void set_color(enum rb_color color, struct rbtree_node *node)
{
	node->parent = (node->parent & ~1UL) | color;
}

static inline struct rbtree_node *get_parent(const struct rbtree_node *node)
{
	return (struct rbtree_node *)(node->parent & ~1UL);
}

static inline void set_parent(struct rbtree_node *parent, struct rbtree_node *node)
{
	node->parent = (uintptr_t)parent | (node->parent & 1);
}

#else

static inline enum rb_color get_color(const struct rbtree_node *node)
{
	return node->color;
}

static inline void set_color(enum rb_color color, struct rbtree_node *node)
{
	node->color = color;
}

static inline struct rbtree_node *get_parent(const struct rbtree_node *node)
{
	return node->parent;
}

static inline void set_parent(struct rbtree_node *parent, struct rbtree_node *node)
{
	node->parent = parent;
}

#endif	/* UINTPTR_MAX */

static inline int is_root(struct rbtree_node *node)
{
	return get_parent(node) == NULL;
}

static inline int is_black(struct rbtree_node *node)
{
	return get_color(node) == RB_BLACK;
}

static inline int is_red(struct rbtree_node *node)
{
	return !is_black(node);
}

/*
 * Iterators
 */
static inline struct rbtree_node *get_first(struct rbtree_node *node)
{
	while (node->left)
		node = node->left;
	return node;
}

static inline struct rbtree_node *get_last(struct rbtree_node *node)
{
	while (node->right)
		node = node->right;
	return node;
}

struct rbtree_node *rbtree_first(const struct rbtree *tree)
{
	return tree->first;
}

struct rbtree_node *rbtree_last(const struct rbtree *tree)
{
	return tree->last;
}

struct rbtree_node *rbtree_next(const struct rbtree_node *node)
{
	struct rbtree_node *parent;

	if (node->right)
		return get_first(node->right);

	while ((parent = get_parent(node)) && parent->right == node)
		node = parent;
	return parent;
}

struct rbtree_node *rbtree_prev(const struct rbtree_node *node)
{
	struct rbtree_node *parent;

	if (node->left)
		return get_last(node->left);

	while ((parent = get_parent(node)) && parent->left == node)
		node = parent;
	return parent;
}

/*
 * 'pparent' and 'is_left' are only used for insertions. Normally GCC
 * will notice this and get rid of them for lookups.
 */
static inline struct rbtree_node *do_lookup(const struct rbtree_node *key,
					    const struct rbtree *tree,
					    struct rbtree_node **pparent,
					    int *is_left)
{
	struct rbtree_node *node = tree->root;

	*pparent = NULL;
	*is_left = 0;

	while (node) {
		int res = tree->cmp_fn(node, key);
		if (res == 0)
			return node;
		*pparent = node;
		if ((*is_left = res > 0))
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

/*
 * Rotate operations (They preserve the binary search tree property,
 * assuming that the keys are unique).
 */
static void rotate_left(struct rbtree_node *node, struct rbtree *tree)
{
	struct rbtree_node *p = node;
	struct rbtree_node *q = node->right; /* can't be NULL */
	struct rbtree_node *parent = get_parent(p);

	if (!is_root(p)) {
		if (parent->left == p)
			parent->left = q;
		else
			parent->right = q;
	} else
		tree->root = q;
	set_parent(parent, q);
	set_parent(q, p);

	p->right = q->left;
	if (p->right)
		set_parent(p, p->right);
	q->left = p;
}

static void rotate_right(struct rbtree_node *node, struct rbtree *tree)
{
	struct rbtree_node *p = node;
	struct rbtree_node *q = node->left; /* can't be NULL */
	struct rbtree_node *parent = get_parent(p);

	if (!is_root(p)) {
		if (parent->left == p)
			parent->left = q;
		else
			parent->right = q;
	} else
		tree->root = q;
	set_parent(parent, q);
	set_parent(q, p);

	p->left = q->right;
	if (p->left)
		set_parent(p, p->left);
	q->right = p;
}

struct rbtree_node *rbtree_lookup(const struct rbtree_node *key,
				  const struct rbtree *tree)
{
	struct rbtree_node *parent;
	int is_left;

	return do_lookup(key, tree, &parent, &is_left);
}

static void set_child(struct rbtree_node *child, struct rbtree_node *node, int left)
{
	if (left)
		node->left = child;
	else
		node->right = child;
}

struct rbtree_node *rbtree_insert(struct rbtree_node *node, struct rbtree *tree)
{
	struct rbtree_node *key, *parent;
	int is_left;

	key = do_lookup(node, tree, &parent, &is_left);
	if (key)
		return key;

	node->left = NULL;
	node->right = NULL;
	set_color(RB_RED, node);
	set_parent(parent, node);

	if (parent) {
		if (is_left) {
			if (parent == tree->first)
				tree->first = node;
		} else {
			if (parent == tree->last)
				tree->last = node;
		}
		set_child(node, parent, is_left);
	} else {
		tree->root = node;
		tree->first = node;
		tree->last = node;
	}

	/*
	 * Fixup the modified tree by recoloring nodes and performing
	 * rotations (2 at most) hence the red-black tree properties are
	 * preserved.
	 */
	while ((parent = get_parent(node)) && is_red(parent)) {
		struct rbtree_node *grandpa = get_parent(parent);

		if (parent == grandpa->left) {
			struct rbtree_node *uncle = grandpa->right;

			if (uncle && is_red(uncle)) {
				set_color(RB_BLACK, parent);
				set_color(RB_BLACK, uncle);
				set_color(RB_RED, grandpa);
				node = grandpa;
			} else {
				if (node == parent->right) {
					rotate_left(parent, tree);
					node = parent;
					parent = get_parent(node);
				}
				set_color(RB_BLACK, parent);
				set_color(RB_RED, grandpa);
				rotate_right(grandpa, tree);
			}
		} else {
			struct rbtree_node *uncle = grandpa->left;

			if (uncle && is_red(uncle)) {
				set_color(RB_BLACK, parent);
				set_color(RB_BLACK, uncle);
				set_color(RB_RED, grandpa);
				node = grandpa;
			} else {
				if (node == parent->left) {
					rotate_right(parent, tree);
					node = parent;
					parent = get_parent(node);
				}
				set_color(RB_BLACK, parent);
				set_color(RB_RED, grandpa);
				rotate_left(grandpa, tree);
			}
		}
	}
	set_color(RB_BLACK, tree->root);
	return NULL;
}

void rbtree_remove(struct rbtree_node *node, struct rbtree *tree)
{
	struct rbtree_node *parent = get_parent(node);
	struct rbtree_node *left = node->left;
	struct rbtree_node *right = node->right;
	struct rbtree_node *next;
	enum rb_color color;

	if (node == tree->first)
		tree->first = rbtree_next(node);
	if (node == tree->last)
		tree->last = rbtree_prev(node);

	if (!left)
		next = right;
	else if (!right)
		next = left;
	else
		next = get_first(right);

	if (parent)
		set_child(next, parent, parent->left == node);
	else
		tree->root = next;

	if (left && right) {
		color = get_color(next);
		set_color(get_color(node), next);

		next->left = left;
		set_parent(next, left);

		if (next != right) {
			parent = get_parent(next);
			set_parent(get_parent(node), next);

			node = next->right;
			parent->left = node;

			next->right = right;
			set_parent(next, right);
		} else {
			set_parent(parent, next);
			parent = next;
			node = next->right;
		}
	} else {
		color = get_color(node);
		node = next;
	}
	/*
	 * 'node' is now the sole successor's child and 'parent' its
	 * new parent (since the successor can have been moved).
	 */
	if (node)
		set_parent(parent, node);

	/*
	 * The 'easy' cases.
	 */
	if (color == RB_RED)
		return;
	if (node && is_red(node)) {
		set_color(RB_BLACK, node);
		return;
	}

	do {
		if (node == tree->root)
			break;

		if (node == parent->left) {
			struct rbtree_node *sibling = parent->right;

			if (is_red(sibling)) {
				set_color(RB_BLACK, sibling);
				set_color(RB_RED, parent);
				rotate_left(parent, tree);
				sibling = parent->right;
			}
			if ((!sibling->left  || is_black(sibling->left)) &&
			    (!sibling->right || is_black(sibling->right))) {
				set_color(RB_RED, sibling);
				node = parent;
				parent = get_parent(parent);
				continue;
			}
			if (!sibling->right || is_black(sibling->right)) {
				set_color(RB_BLACK, sibling->left);
				set_color(RB_RED, sibling);
				rotate_right(sibling, tree);
				sibling = parent->right;
			}
			set_color(get_color(parent), sibling);
			set_color(RB_BLACK, parent);
			set_color(RB_BLACK, sibling->right);
			rotate_left(parent, tree);
			node = tree->root;
			break;
		} else {
			struct rbtree_node *sibling = parent->left;

			if (is_red(sibling)) {
				set_color(RB_BLACK, sibling);
				set_color(RB_RED, parent);
				rotate_right(parent, tree);
				sibling = parent->left;
			}
			if ((!sibling->left  || is_black(sibling->left)) &&
			    (!sibling->right || is_black(sibling->right))) {
				set_color(RB_RED, sibling);
				node = parent;
				parent = get_parent(parent);
				continue;
			}
			if (!sibling->left || is_black(sibling->left)) {
				set_color(RB_BLACK, sibling->right);
				set_color(RB_RED, sibling);
				rotate_left(sibling, tree);
				sibling = parent->left;
			}
			set_color(get_color(parent), sibling);
			set_color(RB_BLACK, parent);
			set_color(RB_BLACK, sibling->left);
			rotate_right(parent, tree);
			node = tree->root;
			break;
		}
	} while (is_black(node));

	if (node)
		set_color(RB_BLACK, node);
}

void rbtree_replace(struct rbtree_node *old, struct rbtree_node *new,
		    struct rbtree *tree)
{
	struct rbtree_node *parent = get_parent(old);

	if (parent)
		set_child(new, parent, parent->left == old);
	else
		tree->root = new;

	if (old->left)
		set_parent(new, old->left);
	if (old->right)
		set_parent(new, old->right);

	if (tree->first == old)
		tree->first = new;
	if (tree->last == old)
		tree->last = new;

	*new = *old;
}

int rbtree_init(struct rbtree *tree, rbtree_cmp_fn_t fn, unsigned long flags)
{
	if (flags)
		return -1;
	tree->root = NULL;
	tree->cmp_fn = fn;
	tree->first = NULL;
	tree->last = NULL;
	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    