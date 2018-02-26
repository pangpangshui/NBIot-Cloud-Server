import Vue from 'vue'
import Router from 'vue-router'
import Index from './../views/index'
import Login from '@/views/login'
import Register from './../views/register'
import Backmangement from './../views/backManagement'
import Coap from './../views/coap'
import Test from '@/components/HelloWorld'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'Index',
      component: Index
    },
    {
      path: '/users/login',
      name: 'Login',
      component: Login
    },
    {
      path: '/users/register',
      name: 'Register',
      component: Register
    },
    {
      path: '/backmangement',
      name: 'Backmangement',
      component: Backmangement
    },
    {
      path: '/coap',
      name: 'Coap',
      component: Coap
    },
    {
      path: '/test',
      name: 'Test',
      component: Test
    }
  ]
})
