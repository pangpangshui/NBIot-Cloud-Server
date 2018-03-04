<template>
  <!--<div id="app">-->
    <!--<img src="./assets/logo.png">-->
  <keep-alive>
    <router-view @loginSuccessfully="loginSuccessfully"></router-view>
  </keep-alive>
  <!--</div>-->
</template>

<script>
export default {
  name: 'App',
  data() {
    return {
      userName: sessionStorage.userName
    }
  },
  methods: {
    loginSuccessfully(userName) {
      sessionStorage.userName = userName;
      this.userName = sessionStorage.userName;
      console.log(sessionStorage.userName);
    }
  }
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
