

#cmd="mysql -u root --password=suP1Cos3 -h 127.0.0.1"
cmd="mysql -u root --password=suP1Cos3 -h 192.168.0.10"

echo 'Remove DB'
$cmd < removedb.sql

echo 'Create DB'
$cmd < createdb.sql

echo 'Lookup Values'
$cmd < bidask.sql
$cmd < boringexciting.sql
#$cmd < candlesource.sql
$cmd < colorchange.sql
$cmd < direction.sql
$cmd < formation.sql
#$cmd < monitoredinstrument.sql
$cmd < supplydemand.sql

echo 'Time Frame'
$cmd < timeframe.sql
$cmd < timeframedata.sql

echo 'Instrument Type'
$cmd < instrumenttype.sql
# $cmd < instrumenttypedata.sql

echo 'Instrument'
$cmd < instrument.sql
#$cmd < instrumentdata.sql

echo 'Instrument Base Timeframe'
$cmd < instrumentbasetimeframe.sql

echo 'Instrument Quote Date'
$cmd < instrumentquotedate.sql

echo 'Candle'
$cmd < candle.sql

echo 'Zone'
$cmd < zone.sql
$cmd < zonestop.sql
$cmd < zoneretracement.sql

echo 'Tick'
$cmd < tick.sql

echo 'Timeframe Quotes'
$cmd < timeframequote.sql

echo 'Views'
$cmd < v_boringexciting.sql
$cmd < v_zoneretracementcount.sql
$cmd < v_candledetail.sql

echo 'Stored Procs'
$cmd < p_firstcrossingcandle.sql
$cmd < p_lastcrossingcandle.sql
$cmd < p_stoppingcandle.sql
$cmd < p_startofstoppingcandle.sql
$cmd < p_stoppingcandles.sql
$cmd < p_maxretracementcandle.sql
$cmd < p_maxpricecandle.sql

