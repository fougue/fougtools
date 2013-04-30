#!/usr/bin/ruby

require 'getoptlong'

# Parse command line
opts = GetoptLong.new(
#  ['--help', '-h', GetoptLong::NO_ARGUMENT],
  ['--namespace', '-n', GetoptLong::REQUIRED_ARGUMENT],
  ['--version', '-v', GetoptLong::REQUIRED_ARGUMENT],
  ['--output', '-o', GetoptLong::REQUIRED_ARGUMENT])

version = String.new
outFileName = String.new
nameSpace = "unknown"
opts.each do |opt, arg|
  case opt
    when '--namespace'
      nameSpace = arg
    when '--version'
      version = arg
    when '--output'
      outFileName = arg
  end
end

# Check if a file name was specified
if outFileName.empty? then
  puts "No output file name specified, abort"
  Process.exit
end

# Check if the file name specified is writable
outs = File.open(outFileName, "w")
if not File.writable?(outFileName) then
  puts "The output file name specified is not writable, abort"
  Process.exit
end

# Create version number file
include_guard = nameSpace.upcase + "_VERSION_NUMBER_H"
outs << "#ifndef #{include_guard}\n"
outs << "#define #{include_guard}\n"
outs << "\n"
outs << "#include <QtCore/QString>\n"
outs << "\n"
outs << "namespace " << nameSpace << " {\n"
outs << "\n"
outs << "const QString versionNumber(\"#{version}\");\n"
outs << "\n"
outs << "} // namespace " << nameSpace << "\n"
outs << "\n"
outs << "#endif // #{include_guard}\n"
