/*
 * This file contains information proprietary to Nullsoft and AOL.  For
 * further information on rules and restrictions governing the use of the
 * SHOUTcast API, the SHOUTcast Directory and other related SHOUTcast
 * services, please visit: http://www.shoutcast.com/tos
 * 
 * For the API we use there is a Developer ID needed. You are not allowed
 * to use the key we use here in your own Applications. You can request a
 * key by filling the Partner Request Form at
 * http://www.shoutcast.com/partner_request_form
 */
 
// Import URL helper
Components.utils.import("resource://app/jsmodules/URLUtils.jsm");

// This is our Developer ID ("API Key") we need to access the SHOUTcast API.
const SB_SHOUTCAST_APIKEY = "sh19qvGfsOJkQ0pv";

// The URL parts we'll use to connect to SHOUTcast's API
const SB_SHOUTCAST_APIURL = "http://api.shoutcast.com/legacy/";
const SB_SHOUTCAST_APITOP500 = "Top500";
const SB_SHOUTCAST_APIGENRE = "genresearch";
// Params we need in every API call:
// - restricting to MP3 to eliminate dependency on
//   AAC decoder being installed
// - the API Key
const SB_SHOUTCAST_APIPARAMS = {mt: "audio/mpeg", k: SB_SHOUTCAST_APIKEY};

// The URL we'll use to tune into a station.
const SB_SHOUTCAST_TUNEURL = "http://yp.shoutcast.com/sbin/tunein-station.pls";

// The class doin' ALL stuff that is SHOUTcast-API related
var ShoutcastRadio = {
  
  // Returns a URL to the pls with the Stream for the given SHOUTcast Stream ID
  getListenURL : function(aId) {
    return URLUtils.addQuery(SB_SHOUTCAST_TUNEURL, {id : aId});
  },
  
  // Returns a URL to get the station list for the given genre.
  getListURL : function(aGenre) {
    var tmpurl;
    // If aGenre is null, we'll search for top stations
    if (aGenre)
      tmpurl = URLUtils.addQuery(SB_SHOUTCAST_APIURL + SB_SHOUTCAST_APIGENRE, {genre : aGenre});
    else
      tmpurl = SB_SHOUTCAST_APIURL + SB_SHOUTCAST_APITOP500;
    return URLUtils.addQuery(tmpurl, SB_SHOUTCAST_APIPARAMS);
  },
  
  // Parses the data from the xml text generated by the SHOUTcast API
  _parseStationListFromXML : function(aXml, aGenre) {
    var result = [];
    // Make sure we recived XML
    if (!aXml)
      return result;
    // Go through all stations and add them to result
    var entries = aXml.getElementsByTagName("station");
    for (var i = 0; i < entries.length; i++){
      var ent = entries[i];
      result.push(
      {
        id : ent.getAttribute("id"),
        // We will use the given genre or the first genre if we're in Top500
        genre : aGenre ? aGenre : ent.getAttribute("genre").split(" ")[0],
        bitrate : ent.getAttribute("br"),
        numListeners : ent.getAttribute("lc"),
        currentTrack : ent.getAttribute("ct"),
        // We will remove the '- a SHOUTcast.com member station' at every name's end
        name : ent.getAttribute("name").split(" - a SHOUTcast.com member station")[0]
      });
    }
    return result;
  },
  
  // Returns a Stream-Array for the given genre
  getStationList : function(aGenre) {
    var req = new XMLHttpRequest();
    // Set aGenre null if we search for the top streams
    if (aGenre == "sbITop")
      aGenre = null;
    req.open("POST",
      this.getListURL(aGenre), false);
    req.genre = aGenre;
    var stationList = [];
    try {
      req.send(null);
      stationList = this._parseStationListFromXML(req.responseXML, aGenre);
    } catch (e) {} // Drop connection errors, we'll return an empty array
    return (stationList);
  }
}