##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Test
ProjectName            :=UOCTransport
ConfigurationName      :=Test
WorkspacePath          :=/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu
ProjectPath            :=/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu
IntermediateDirectory  :=./Test
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=uoc
Date                   :=04/06/21
CodeLitePath           :=/home/uoc/.codelite
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="UOCTransport.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch)./include $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IntermediateDirectory)/src_material.c$(ObjectSuffix) $(IntermediateDirectory)/src_location.c$(ObjectSuffix) $(IntermediateDirectory)/src_truck.c$(ObjectSuffix) $(IntermediateDirectory)/src_delivery.c$(ObjectSuffix) $(IntermediateDirectory)/src_stack.c$(ObjectSuffix) $(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IntermediateDirectory)/src_menu.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Test || $(MakeDirCommand) ./Test


$(IntermediateDirectory)/.d:
	@test -d ./Test || $(MakeDirCommand) ./Test

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_api.c$(ObjectSuffix): src/api.c $(IntermediateDirectory)/src_api.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/api.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_api.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_api.c$(DependSuffix): src/api.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_api.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_api.c$(DependSuffix) -MM src/api.c

$(IntermediateDirectory)/src_api.c$(PreprocessSuffix): src/api.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_api.c$(PreprocessSuffix) src/api.c

$(IntermediateDirectory)/src_material.c$(ObjectSuffix): src/material.c $(IntermediateDirectory)/src_material.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/material.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_material.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_material.c$(DependSuffix): src/material.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_material.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_material.c$(DependSuffix) -MM src/material.c

$(IntermediateDirectory)/src_material.c$(PreprocessSuffix): src/material.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_material.c$(PreprocessSuffix) src/material.c

$(IntermediateDirectory)/src_location.c$(ObjectSuffix): src/location.c $(IntermediateDirectory)/src_location.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/location.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_location.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_location.c$(DependSuffix): src/location.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_location.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_location.c$(DependSuffix) -MM src/location.c

$(IntermediateDirectory)/src_location.c$(PreprocessSuffix): src/location.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_location.c$(PreprocessSuffix) src/location.c

$(IntermediateDirectory)/src_truck.c$(ObjectSuffix): src/truck.c $(IntermediateDirectory)/src_truck.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/truck.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_truck.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_truck.c$(DependSuffix): src/truck.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_truck.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_truck.c$(DependSuffix) -MM src/truck.c

$(IntermediateDirectory)/src_truck.c$(PreprocessSuffix): src/truck.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_truck.c$(PreprocessSuffix) src/truck.c

$(IntermediateDirectory)/src_delivery.c$(ObjectSuffix): src/delivery.c $(IntermediateDirectory)/src_delivery.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/delivery.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_delivery.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_delivery.c$(DependSuffix): src/delivery.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_delivery.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_delivery.c$(DependSuffix) -MM src/delivery.c

$(IntermediateDirectory)/src_delivery.c$(PreprocessSuffix): src/delivery.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_delivery.c$(PreprocessSuffix) src/delivery.c

$(IntermediateDirectory)/src_stack.c$(ObjectSuffix): src/stack.c $(IntermediateDirectory)/src_stack.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/stack.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_stack.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_stack.c$(DependSuffix): src/stack.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_stack.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_stack.c$(DependSuffix) -MM src/stack.c

$(IntermediateDirectory)/src_stack.c$(PreprocessSuffix): src/stack.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_stack.c$(PreprocessSuffix) src/stack.c

$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c $(IntermediateDirectory)/src_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(DependSuffix): src/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.c$(DependSuffix) -MM src/main.c

$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) src/main.c

$(IntermediateDirectory)/src_test.c$(ObjectSuffix): src/test.c $(IntermediateDirectory)/src_test.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/test.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_test.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_test.c$(DependSuffix): src/test.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_test.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_test.c$(DependSuffix) -MM src/test.c

$(IntermediateDirectory)/src_test.c$(PreprocessSuffix): src/test.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_test.c$(PreprocessSuffix) src/test.c

$(IntermediateDirectory)/src_menu.c$(ObjectSuffix): src/menu.c $(IntermediateDirectory)/src_menu.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/sf_carpeta_compartida_Maquina_Virtual/fsuchesparza_pr2/UOCTransport_PR2_enu/src/menu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_menu.c$(DependSuffix): src/menu.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_menu.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_menu.c$(DependSuffix) -MM src/menu.c

$(IntermediateDirectory)/src_menu.c$(PreprocessSuffix): src/menu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_menu.c$(PreprocessSuffix) src/menu.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Test/


