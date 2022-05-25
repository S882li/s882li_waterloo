import { useState } from 'react';
import io from 'socket.io-client'
import './App.css';
import TextField from '@mui/material/TextField';
import { Button, Stack, Box } from '@mui/material';
import Chat from './Chat';
import Topic from './Topic';

const socket = io.connect("http://localhost:3001")

function App() {

  const [username, setUsername] = useState("");
  const [room, setRoom] = useState("");
  const [showChat, setShowChat] = useState(false);


  const joinRoom = () => {
    if (username !== "" && room !== "") {
      socket.emit("join_room", room);
      setShowChat(true);
    }
  };
  return (

    <Stack direction={"row"} spacing={2}>
      <Box sx={{ width: 300 }}>
        {!showChat ? (
          <Stack sx={{ margin: 1 }}>
            <TextField id="outlined-basic" label="UserName" variant="outlined" margin="normal" onChange={(event) => { setUsername(event.target.value) }} />
            <TextField id="outlined-basic" label="Room" variant="outlined" margin="normal" onChange={(event) => { setRoom(event.target.value) }} />
            <Button variant="contained" onClick={joinRoom} >JOIN</Button>
          </Stack>
        ) : (
          <Chat socket={socket} username={username} room={room}></Chat>
        )}
      </Box>
      <Box sx={{
      overflow: 'auto',
      height: '450px',
      width: 300,
      margin: 1,
      padding: 1,
      border: 1,
      display: 'flex',
      flexDirection: 'column',
      borderRadius: 1,
      borderColor: 'grey.500'
    }}>
        <Topic socket={socket} username={username} room={room}></Topic>
      </Box>
      
      
    </Stack>
  );
}

export default App;
