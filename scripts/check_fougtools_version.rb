#!/usr/bin/ruby

result = 1

argVersionStr = String(ARGV.first)
fougToolsVersionStr = String("?.?.?")
if not argVersionStr.empty? then
  argVersionMajMinPat = argVersionStr.split('.')
  
  scriptsDirName = File.expand_path(File.dirname(__FILE__))
  fougtoolsGlobalFileContents = File.open("#{scriptsDirName}/../include/fougtools_global.h", "r").read
  fougToolsVersionStr = fougtoolsGlobalFileContents.scan(/FOUGTOOLS_VERSION_STR\s+"([0-9].[0-9].[0-9])"/).join
  fougToolsVersionMajMinPat = fougToolsVersionStr.split('.')
  if fougToolsVersionMajMinPat.size >= argVersionMajMinPat.size and
     argVersionMajMinPat.size >= 2
  then
     if fougToolsVersionMajMinPat[0].to_i == argVersionMajMinPat[0].to_i and
         fougToolsVersionMajMinPat[1].to_i == argVersionMajMinPat[1].to_i and
         (argVersionMajMinPat.size == 2 or
           (argVersionMajMinPat.size >= 3 and
            fougToolsVersionMajMinPat[2].to_i >= argVersionMajMinPat[2].to_i))
     then
       result = 0
     end
  end
end

puts "FougTools v#{fougToolsVersionStr}, #{result == 0 ? "OK" : "check failed"}"
Kernel.exit(result == 0)