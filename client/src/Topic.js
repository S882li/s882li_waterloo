import React from 'react';
import {nanoid} from 'nanoid';
import { useState, useEffect } from 'react';

function Topic(socket, username, room) {
  const [currentTopic, setCurrentTopic] = useState('');
  const [currentDescription, setCurrentDescription] = useState('');
  const [TopicList, setTopicList] = useState([]);
  const [fromTime, setfromTime] = useState();
  const [toTime, setToTime] = useState();

  const sendTopic = async () => {
    if (currentTopic && currentDescription && fromTime && toTime) {
      const TopicData = {
        id: nanoid(),
        author: username,
        Topic: currentTopic,
        fromTime: fromTime,
        toTime: toTime
      };

      await socket.emit("send_topic", TopicData);
      setTopicList((list) => [...list, TopicData]);
      setCurrentTopic("");
      setCurrentTopic("");
    }
  };
/*
  useEffect(() => {
    socket.on("receive_topic", (data) => {
      console.log(data);
      setTopicList((list) => [...list, data]);
      setTopicList((list) => list.filter((ele, pos) => list.indexOf(ele) === pos));
    })
  }, [socket]) */


  return (
    <div>Topic</div>
  )
}

export default Topic