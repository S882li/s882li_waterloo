import { Button, TextField, Typography, Stack, Box } from '@mui/material';
import React, { useEffect, useState } from 'react'; //rfce


function Chat({ socket, username, room }) {
  const [currentMessage, setCurrentMessage] = useState('');
  const [messageList, setMessageList] = useState([]);

  const sendMessage = async () => {
    if (currentMessage !== "") {
      const messageData = {
        room: room,
        author: username,
        message: currentMessage,
        time:
          new Date(Date.now()).getHours() +
          ":" +
          new Date(Date.now()).getMinutes(),
      };

      await socket.emit("send_message", messageData);
      setMessageList((list) => [...list, messageData]);
      setCurrentMessage("");
    }
  };

  useEffect(() => {
    socket.on("receive_message", (data) => {
      console.log(data);
      setMessageList((list) => [...list, data]);
      setMessageList((list) => list.filter((ele, pos) => list.indexOf(ele) === pos));
    })
  }, [socket])


  return (
    <Box sx={{
      overflow: 'auto',
      height: '450px',
      margin: 1,
      padding: 1,
      border: 1,
      display: 'flex',
      flexDirection: 'column',
      borderRadius: 1,
      borderColor: 'grey.500'
    }}>
      <Typography variant="h5" sx={{ display: 'block', textAlign: 'center' }} > {'Room ' + room} </Typography>
      <Stack className='chat-body' spacing={2} sx={{
        overflow: 'auto',
        height: '320px',
      }}>
        {messageList.map((messageContent) => {
          return <Stack>
            {messageContent.author !== username?

            
            <Stack>
              <Typography sx={{
                //color: 'grey.500',
                fontSize: 'small'
              }}>
                {messageContent.author}
              </Typography>
              <Typography classname='chat-bubble' sx={{
                borderRadius: 2,
                width: 'auto',
                alignText: 'right',
                padding: 1,
                color: 'white',
                backgroundColor: '#1976D2'
              }}> {messageContent.message}
              </Typography>
              <Typography sx={{
                color: 'grey.500',
                fontSize: '25%'
              }}>
                {messageContent.time}
              </Typography>
            </Stack>
          : 
          <Stack>
              <Typography sx={{
                fontSize: 'small'
              }}>
                You
              </Typography>
              <Typography classname='chat-bubble' sx={{
                borderRadius: 2,
                alignText: 'right',
                padding: 1,
               
                backgroundColor: '#e1e1e1'
              }}> {messageContent.message}
              </Typography>
              <Typography sx={{
                color: 'grey.500',
                fontSize: '25%'
              }}>
                {messageContent.time}
              </Typography>
            </Stack>
          
          
          }

          </Stack>

        })}
      </Stack >
      <Stack spacing={1}>
        <TextField id="standard-basic" label={username} variant="standard" value={currentMessage} onChange={(event) => { setCurrentMessage(event.target.value) }} />
        <Button variant='contained' onClick={sendMessage}>
          Send
        </Button>
      </Stack>
    </Box >
  )
}

export default Chat;