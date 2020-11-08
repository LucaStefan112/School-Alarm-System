const electron = require("electron");
const app = electron.app;
const BrowserWindow = electron.BrowserWindow;
const path = require("path");
const url = require("url");
const ipc = electron.ipcMain;

let pauza = false;

function createWindow(winUrl, devTools, hidden){
	let win = new BrowserWindow({
        webPreferences: {
            nodeIntegration: true
        }
    });

	if(hidden)	win.hide();

	win.loadURL(url.format({
		pathname: path.join(__dirname, winUrl.toString()),
		protocol: 'file',
		slashes: true
	}));

	if(devTools)	win.webContents.openDevTools();

	win.on('closed', () => win = null);
	
	return win;
}

async function running(){
	setInterval(() => {
		let currentDate = new Date();
		let ora = currentDate.getHours();
		let minut = currentDate.getMinutes();

		if((7 < ora && ora < 11 && (minut == 0 || minut == 50)) || (10 < ora && ora < 16 && (minut == 10 || minut == 0)) && !(ora == 11 && minut == 0)){
	            if(!pauza){
	                createWindow('alarmSound.html', false, true);
	                pauza = true;
	            }}
	    else
	        pauza = false;}, 100);
}

app.on('ready', () => {createWindow('index.html', false, true);running();});