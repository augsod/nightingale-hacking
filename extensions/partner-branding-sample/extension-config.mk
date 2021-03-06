#
# Copyright (c) 2008, Pioneers of the Inevitable, Inc.
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 	* Redistributions of source code must retain the above copyright notice,
# 	  this list of conditions and the following disclaimer.
# 	* Redistributions in binary form must reproduce the above copyright notice,
# 	  this list of conditions and the following disclaimer in the documentation 
# 	  and/or other materials provided with the distribution.
# 	* Neither the name of Pioneers of the Inevitable, Songbird, nor the names
# 	  of its contributors may be used to endorse or promote products derived
# 	  from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 

EXTENSION_NAME = partner-branding-sample
EXTENSION_UUID = $(EXTENSION_NAME)@songbirdnest.com
EXTENSION_NO_BINARY_COMPONENTS = 1

EXTENSION_VER = 1.0.3pre
EXTENSION_MIN_VER = $(SB_JSONLY_EXTENSION_MIN_VER)
EXTENSION_MAX_VER = $(SB_JSONLY_EXTENSION_MAX_VER)

# For ease-of-handling (and since this is not an official extension we 
# really care about, use a simpler .xpi name that's consisten. 

XPI_NAME = $(EXTENSION_NAME)-$(EXTENSION_VER).xpi

# Change our branding to be partner branding; this is relative to topsrcdir
# and expects to find a branding.mk in that directory
SONGBIRD_BRANDING_DIR = extensions/$(EXTENSION_NAME)
