CMAKE_MINIMUM_REQUIRED ( VERSION 3.11 )
PROJECT ( vOscillation )
SET ( CMAKE_VERBOSE_MAKEFILE true )

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

