#############################################################################
##  FougTools
##  Copyright Fougue (30 Mar. 2015)
##  contact@fougue.pro
##
## This software is a computer program whose purpose is to provide utility
## tools for the C++ language and the Qt toolkit.
##
## This software is governed by the CeCILL-C license under French law and
## abiding by the rules of distribution of free software.  You can  use,
## modify and/ or redistribute the software under the terms of the CeCILL-C
## license as circulated by CEA, CNRS and INRIA at the following URL
## "http://www.cecill.info".
#############################################################################

#!/usr/bin/ruby

require 'getoptlong'

def isWinPlatform()
    return RUBY_PLATFORM =~ /mingw|mswin/
end

def checkFileExists(file)
    if not File.exists?(file) then
        puts "Warning: '#{file}' does not exist"
    end
end

def asQMakePath(file)
    if isWinPlatform() then
        return file.gsub("\\", "/")
    else
        return file
    end
end

def addQMakeConfigFlag(file, flagOn, flagName)
    if flagOn then
        file.puts("CONFIG += #{flagName}")
    end
end

def printHelp()
    puts "Usage: configure.rb [--help|-h]"
    puts ""
    puts "         --prefix <dir> ............. This will install everything relative to <dir>"
    puts "                                      (default PWD/local)"
    puts ""
    puts "      *  --shared-libs .............. Build shared libraries (DLL)"
    puts "         --static-libs .............. Build static libraries"
    puts ""
    puts "         --occ-debug-dir ............ Open Cascade root directory, debug variant"
    puts "                                      Useful only with --occtools"
    puts "         --occ-release-dir .......... Open Cascade root directory, release variant"
    puts "                                      Useful only with --occtools"
    puts ""
    puts "      *  --no-occtools .............. Do not compile occtools"
    puts "         --occtools ................. Compile occtools"
    puts "                                      Requires OpenCascade (see --occ-dir)"
    puts ""
    puts "         --utest .................... Build unit tests"
    puts "         --examples ................. Build unit examples"
    puts ""
end

# Parse command line
configArgs = ARGV.join(' ')
opts = GetoptLong.new(
    ['--help', '-h', GetoptLong::NO_ARGUMENT],
    ['--prefix', GetoptLong::REQUIRED_ARGUMENT],
    ['--occ-debug-dir', GetoptLong::REQUIRED_ARGUMENT],
    ['--occ-release-dir', GetoptLong::REQUIRED_ARGUMENT],
    ['--no-occtools', GetoptLong::NO_ARGUMENT],
    ['--occtools', GetoptLong::NO_ARGUMENT],
    ['--shared-libs', GetoptLong::NO_ARGUMENT],
    ['--static-libs', GetoptLong::NO_ARGUMENT],
    ['--utest', GetoptLong::NO_ARGUMENT],
    ['--examples', GetoptLong::NO_ARGUMENT]
)

optValues = {
    :prefix => "$$PWD/local",
    :occDebugDir => "/opt/def/occ_debug",
    :occReleaseDir => "/opt/def/occ_release",
    :occTools => false,
    :sharedLibs => true,
    :utest => false,
    :examples => false
}

opts.each do |opt, arg|
    case opt
        when '--help'
            printHelp()
            exit
        when '-h'
            printHelp()
            exit
        when '--prefix'
            optValues[:prefix] = arg
        when '--occ-debug-dir'
            optValues[:occDebugDir] = arg
        when '--occ-release-dir'
            optValues[:occReleaseDir] = arg
        when '--no-occtools'
            optValues[:occTools] = false
        when '--occtools'
            optValues[:occTools] = true
        when '--shared-libs'
            optValues[:sharedLibs] = true
        when '--static-libs'
            optValues[:sharedLibs] = false
        when '--utest'
            optValues[:utest] = true
        when '--examples'
            optValues[:examples] = true
    end
end

File.open('_local_config.pri', 'w') do |f|
    f.puts("PREFIX_DIR = #{asQMakePath(File.expand_path(optValues[:prefix]))}")
    addQMakeConfigFlag(f, optValues[:occTools], "occtools")
    if optValues[:occTools] then
        checkFileExists(optValues[:occDebugDir])
        checkFileExists(optValues[:occReleaseDir])
        f.puts("CONFIG(debug, debug|release) {")
        f.puts("    CASCADE_ROOT = #{asQMakePath(File.expand_path(optValues[:occDebugDir]))}")
        f.puts("} else {")
        f.puts("    CASCADE_ROOT = #{asQMakePath(File.expand_path(optValues[:occReleaseDir]))}")
        f.puts("}")
    end

    addQMakeConfigFlag(f, optValues[:sharedLibs], "shared_libs")
    addQMakeConfigFlag(f, !optValues[:sharedLibs], "static_libs")
    addQMakeConfigFlag(f, optValues[:utest], "build_utest")
    addQMakeConfigFlag(f, optValues[:examples], "build_examples")
end

# Output configure cache
File.open('_configure.cache', 'w') do |f|
    f.puts("configure.rb #{configArgs}")
end
