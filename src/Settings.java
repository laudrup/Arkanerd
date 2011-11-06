/*
    Settings.java

    Arkanerd - An Arkanoid/Breakout like game for J2ME mobile phones
    Copyright (C) 2006  Kasper Laudrup

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

package arkanerd;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import javax.microedition.rms.RecordStore;
import javax.microedition.rms.RecordStoreException;

public class Settings {

	private final String STORE_NAME = "Settings";
	private RecordStore records;
	public int record_id;
	private int high_score;
	private boolean music_on;

	public Settings() {
		try {
			records = RecordStore.openRecordStore(STORE_NAME, true);
			if(records.getNumRecords() == 0) {
				high_score = 0;
				music_on = true;
			} else loadConfig();
		} catch (RecordStoreException e) {}
	}

	public void setHighScore(int h) {
		high_score = h;
	}

	public int getHighScore() {
		return high_score;
	}

	public void setMusic(boolean b) {
		music_on = b;
	}

	public boolean musicOn() {
		return music_on;
	}

	public void saveConfig() {
		ByteArrayOutputStream bout = new ByteArrayOutputStream();
		DataOutputStream dout = new DataOutputStream(bout);

		try {
		    dout.writeInt(high_score);
		    dout.writeBoolean(music_on);
		    dout.close();

		    byte[] data = bout.toByteArray();
			if(records.getNumRecords() == 0)
				records.addRecord(data, 0, data.length);
			else records.setRecord(1, data, 0, data.length);
		}
		catch(RecordStoreException e) {}
		catch(IOException e) {}
	}

	private void loadConfig() {
		ByteArrayInputStream bin;
		DataInputStream din;

		try {
		    byte[] data = records.getRecord(1);

		    bin = new ByteArrayInputStream( data );
		    din = new DataInputStream( bin );

		    high_score = din.readInt();
		    music_on = din.readBoolean();

		    din.close();

		}
		catch(RecordStoreException e) {}
		catch(IOException e) {}
	}
}