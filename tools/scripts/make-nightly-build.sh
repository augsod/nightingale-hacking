#!/bin/bash

notice() {
  echo $* 1>&2
}

DEPTH=../..
CURRENT_DIR=`pwd`

SONGBIRD_OFFICIAL=1
UPDATE_CHANNEL="nightly"
SB_ENABLE_JARS=1
SB_ENABLE_INSTALLER=1

cd ${DEPTH}
make -f songbird.mk clobber
make -f songbird.mk

notice
notice "Done. MAR and snippet are in compiled/update."
notice "Please copy these files to a safe location!"
notice "They are required to generate the update for the next build."
notice
