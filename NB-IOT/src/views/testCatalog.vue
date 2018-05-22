<script>
  export default {
    name: "test-catalog",
    // const app = new Vue({
    //   el: '#chat',
      data() {
        return {
          newMessageContent: '',
          messages: [{user_id: 1, content:'hey guys'}, {user_id: 2, content:'hey, this is Bob'}, {user_id: 3, content:'Hi, this is Steve'}]
        }

      },
      methods: {
        addMessage: function() {
          // 'this' refers to 'app'.
          this.messages.push({user_id: 1, content: this.newMessageContent});
          this.newMessageContent = '';
        }
      }
    // })
  };
</script>

<template>
  <div id="chat">
    <div id="messages-window">
      <span v-bind:class="'message ' + (message.user_id==1 ? 'ours' : 'theirs')" v-for="message in messages">{{message.content}}</span>
    </div>
    <input type="text" v-model="newMessageContent" v-on:keyup.enter="addMessage"/>
  </div>
</template>

<style scoped>
  html, body {
    height:100%;
  font-family: 'SF UI Text', 'San Francisco Text', Roboto, -apple-system, sans-serif;
  }

  #chat {
    height: 100%;
    overflow: hidden;
    display: flex;
    flex-flow: column;
  }

  #messages-window {
    background:#eee;
    flex: 1 0 auto;
  display: flex;
    flex-direction: column;
  justify-content: flex-end;
  overflow: auto;
    align-items:flex-start;
  padding:20px;
  }

  .message {
    background:gray;
    color:white;
    padding:8px 12px;
    margin-bottom:8px;
    border-radius:16px;
    max-width:70%;
  }

  .ours {
    background:#0076FF;
    align-self:flex-end;
  }

  input {
    padding:10px;
  }

</style>
