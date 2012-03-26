include(SbDistribute)

sb_distribute(
  blocklist.xml
  updater.ini)

sb_distribute_preprocess(
  application.ini
  nightingale.ini)
