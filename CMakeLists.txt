CMAKE_MINIMUM_REQUIRED ( VERSION 3.11 )
SET ( CMAKE_VERBOSE_MAKEFILE true )

PROJECT ( vOscillation )

ADD_LIBRARY ( vOscillation SHARED
    src/vBetaSpectrum.cc
    src/vDetector.cc
    src/vDetectorCylinder.cc
    src/vDetectorSphere.cc
    src/vIBD.cc
    src/vModelGenerator.cc
    src/vModelGeneratorLBL.cc
    src/vModelGeneratorSterileEE.cc
    src/vOscillation.cc
    src/vReactorSpectrum.cc
    src/vScatteringve.cc
    src/vSolarFlux.cc
    src/vSourceCylinder.cc
    src/vSourceSphere.cc
    src/vSterile.cc
    src/vSterileEE.cc
    )

execute_process ( COMMAND root-config --incdir OUTPUT_VARIABLE incdir )
execute_process ( COMMAND root-config --cflags OUTPUT_VARIABLE cflags )
execute_process ( COMMAND root-config --libs   OUTPUT_VARIABLE libs   )

STRING(STRIP ${incdir} incdir)
STRING(STRIP ${cflags} cflags)
STRING(STRIP ${libs}   libs)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cflags} ${libs}")

