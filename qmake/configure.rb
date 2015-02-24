#############################################################################
##
##  FougTools
##  Copyright FougSys (1 Mar. 2011)
##  contact@fougsys.fr
##
## This software is a computer program whose purpose is to provide utility
## tools for the C++ language and the Qt toolkit.
##
## This software is governed by the CeCILL-C license under French law and
## abiding by the rules of distribution of free software.  You can  use,
## modify and/ or redistribute the software under the terms of the CeCILL-C
## license as circulated by CEA, CNRS and INRIA at the following URL
## "http://www.cecill.info".
##
## As a counterpart to the access to the source code and  rights to copy,
## modify and redistribute granted by the license, users are provided only
## with a limited warranty  and the software's author,  the holder of the
## economic rights,  and the successive licensors  have only  limited
## liability.
##
## In this respect, the user's attention is drawn to the risks associated
## with loading,  using,  modifying and/or developing or reproducing the
## software by the user in light of its specific status of free software,
## that may mean  that it is complicated to manipulate,  and  that  also
## therefore means  that it is reserved for developers  and  experienced
## professionals having in-depth computer knowledge. Users are therefore
## encouraged to load and test the software's suitability as regards their
## requirements in conditions enabling the security of their systems and/or
## data to be ensured and,  more generally, to use and operate it in the
## same conditions as regards security.
##
## The fact that you are presently reading this means that you have had
## knowledge of the CeCILL-C license and that you accept its terms.
##
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

def printHelp()
  puts "Usage: configure.rb [--help|-h]"
  puts ""
  puts "         --prefix <dir> ............. This will install everything relative to <dir>"
  puts "                                      (default PWD/local)"
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
  puts "      *  --shared-libs .............. Build shared libraries (DLL)"
  puts "         --static-libs .............. Build static libraries"
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
  ['--static-libs', GetoptLong::NO_ARGUMENT])

options = { :prefix => "$$PWD/local",
            :occDebugDir => "/opt/def/occ_debug",
            :occReleaseDir => "/opt/def/occ_release",
            :occTools => false,
            :sharedLibs => true}
opts.each do |opt, arg|
  case opt
    when '--help'
      printHelp()
      exit
    when '-h'
      printHelp()
      exit
    when '--prefix'
      options[:prefix] = arg
    when '--occ-debug-dir'
      options[:occDebugDir] = arg
    when '--occ-release-dir'
      options[:occReleaseDir] = arg
    when '--no-occtools'
      options[:occTools] = false
    when '--occtools'
      options[:occTools] = true
    when '--shared-libs'
      options[:sharedLibs] = true
    when '--static-libs'
      options[:sharedLibs] = false
  end
end

File.open('_local_config.pri', 'w') do |f|
  f.puts("PREFIX_DIR = #{asQMakePath(File.expand_path(options[:prefix]))}")
  if options[:occTools] then
    checkFileExists(options[:occDebugDir])
    checkFileExists(options[:occReleaseDir])
    f.puts("CONFIG += occtools")
    f.puts("CONFIG(debug, debug|release) {")
    f.puts("  CASCADE_ROOT = #{asQMakePath(File.expand_path(options[:occDebugDir]))}")
    f.puts("} else {")
    f.puts("  CASCADE_ROOT = #{asQMakePath(File.expand_path(options[:occReleaseDir]))}")
    f.puts("}")
  end

  if options[:sharedLibs] then
    f.puts("CONFIG += shared_libs")
  else
    f.puts("CONFIG += static_libs")
  end
end

# Output configure cache
File.open('_configure.cache', 'w') do |f|
  f.puts("configure.rb #{configArgs}")
end
