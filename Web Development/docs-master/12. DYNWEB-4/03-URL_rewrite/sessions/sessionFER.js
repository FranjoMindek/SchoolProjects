const express = require('express');
const uuid = require('uuid')
const url = require('url')


//default values
const DEFAULT_SESSION_TIMEOUT = 1200000;     //20 minutes (in miliseconds)
const DEFALUT_SESSION_ID_NAME = "sID"

//session record store
let sessionStore = new Map();

//session timeout (in ms)
let sessionTimeout = DEFAULT_SESSION_TIMEOUT;
let sIDName = DEFALUT_SESSION_ID_NAME;

function sessionManager(req, res, next) {

    //extract sessionID from GET or POST request
    let sessionID = (req.query[sIDName] || req.body[sIDName]);
    console.log("Received sessionID: " + sessionID)

    //fetch the session record
    let sidRecord = sessionStore.get(sessionID);

    if( sidRecord !== undefined )
        console.log("Fetched session record: " + JSON.stringify(sidRecord))
    else
        console.log("Session record not found for sessionID: " + sessionID)

    //check for session timeout
    if( (sidRecord) && ((sidRecord.lastUsed + sessionTimeout) < Date.now())) {
        sessionStore.delete(sidRecord.id);
        sidRecord = undefined;
        console.log("Session expired: " + sessionID)
    }

    //if the session record does not exist, create one
    if(!sidRecord) {
        sidRecord = {id: uuid.v4(), created: Date.now()};
        sessionStore.set(sidRecord.id, sidRecord)

        console.log("Created new session record " + sIDName + ": " + sidRecord.id)
    }
    
    //update the last used timestamp
    sidRecord.lastUsed = Date.now();

    //add the session record to the request object
    req.session = sidRecord;

    console.log("Session data attached to the request object: " + JSON.stringify(sidRecord) + "\n")

    //pass the control to the next middleware layer
    next();
}


//create a function for adding sessionID to URL
function sessionURLBuilder(sessionID) {

    //add sessionID parameter to URL query segment
    return function(url) {
        let newURL = new URL(url)
        newURL.searchParams.append(sIDName, sessionID)

        return newURL.toString()
    }
}

module.exports = {sessionManager, sessionURLBuilder};
